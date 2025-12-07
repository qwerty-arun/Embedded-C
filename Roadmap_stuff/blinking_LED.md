# Blinking LED (register simulation) — plain C (no hardware)

Below are compact, self-contained C examples that simulate a memory-mapped GPIO register block and implement a blinking LED purely in software. Pick the style you prefer:

* **Example A — simple polling loop** (single-threaded, easy to follow)
* **Example B — timer thread** (simulates hardware timer/ISR using a thread)

Both simulate registers (DIR, DATA/OUT) and show register values and LED state on the console.

---

# Example A — Simple polling loop (register semantics)

```c
// sim_blink.c
// Compile: gcc -std=c11 -O2 -Wall -o sim_blink sim_blink.c
// Run: ./sim_blink

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include <stdbool.h>

typedef uint32_t reg32;

// Simulated GPIO register block
typedef struct {
    reg32 DIR;   // direction: 1 = output, 0 = input
    reg32 OUT;   // output register (what would be driven on pins)
    reg32 IN;    // input register (what would be read from pins)
} GPIO_Regs;

// Simulated memory-mapped GPIO at address "0x40000000"
static GPIO_Regs SIM_GPIO = {0};

// Abstraction helpers
static inline void gpio_set_dir(GPIO_Regs *g, uint8_t pin, bool is_output) {
    if (is_output) g->DIR |= (1u << pin);
    else           g->DIR &= ~(1u << pin);
}

static inline void gpio_write_pin(GPIO_Regs *g, uint8_t pin, bool value) {
    if (g->DIR & (1u << pin)) {       // only affect OUT if pin configured as output
        if (value) g->OUT |= (1u << pin);
        else       g->OUT &= ~(1u << pin);
    } else {
        // writing to an input pin does nothing in this simulation
    }
}

static inline bool gpio_read_pin(GPIO_Regs *g, uint8_t pin) {
    // If pin is input, return IN bit; if output, return OUT bit (reflects what is driven)
    if (g->DIR & (1u << pin)) return (g->OUT >> pin) & 1u;
    else                      return (g->IN  >> pin) & 1u;
}

static inline void gpio_toggle_pin(GPIO_Regs *g, uint8_t pin) {
    if (g->DIR & (1u << pin)) {
        g->OUT ^= (1u << pin);
    }
}

// simple portable sleep in milliseconds
static void msleep(long ms) {
    struct timespec req = { ms / 1000, (ms % 1000) * 1000000L };
    nanosleep(&req, NULL);
}

int main(void) {
    GPIO_Regs *gpio = &SIM_GPIO;
    const uint8_t LED_PIN = 3;      // choose pin number for LED
    const int BLINK_MS = 500;       // blink period half (toggle every 500ms -> 1 Hz)

    // 1) Configure LED pin as output
    gpio_set_dir(gpio, LED_PIN, true);

    printf("Starting LED blink simulation on pin %u (toggle every %d ms)\n", LED_PIN, BLINK_MS);

    // simulate for 10 toggles
    for (int i = 0; i < 10; ++i) {
        gpio_toggle_pin(gpio, LED_PIN);
        bool state = gpio_read_pin(gpio, LED_PIN);

        // Pretty-print register snapshot
        printf("Tick %2d: LED=%s | DIR=0x%08" PRIX32 " OUT=0x%08" PRIX32 " IN=0x%08" PRIX32 "\n",
               i+1,
               state ? "ON " : "OFF",
               gpio->DIR, gpio->OUT, gpio->IN);

        msleep(BLINK_MS);
    }

    printf("Simulation complete.\n");
    return 0;
}
```

Sample output (your output will vary):

```
Starting LED blink simulation on pin 3 (toggle every 500 ms)
Tick  1: LED=ON  | DIR=0x00000008 OUT=0x00000008 IN=0x00000000
Tick  2: LED=OFF | DIR=0x00000008 OUT=0x00000000 IN=0x00000000
Tick  3: LED=ON  | DIR=0x00000008 OUT=0x00000008 IN=0x00000000
...
```

---

# Example B — Timer thread (simulates a hardware timer/ISR)

This version spawns a thread that toggles the LED at a fixed interval while the main thread can do other work or print a running status continuously. Requires `-pthread`.

```c
// sim_blink_thread.c
// Compile: gcc -std=c11 -O2 -Wall -pthread -o sim_blink_thread sim_blink_thread.c
// Run: ./sim_blink_thread

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>

typedef uint32_t reg32;
typedef struct { reg32 DIR; reg32 OUT; reg32 IN; } GPIO_Regs;
static GPIO_Regs SIM_GPIO = {0};

static pthread_mutex_t gpio_lock = PTHREAD_MUTEX_INITIALIZER;

static inline void gpio_set_dir(GPIO_Regs *g, uint8_t pin, bool is_output) {
    pthread_mutex_lock(&gpio_lock);
    if (is_output) g->DIR |= (1u << pin);
    else           g->DIR &= ~(1u << pin);
    pthread_mutex_unlock(&gpio_lock);
}

static inline void gpio_toggle_pin(GPIO_Regs *g, uint8_t pin) {
    pthread_mutex_lock(&gpio_lock);
    if (g->DIR & (1u << pin)) {
        g->OUT ^= (1u << pin);
    }
    pthread_mutex_unlock(&gpio_lock);
}

static inline bool gpio_read_pin(GPIO_Regs *g, uint8_t pin) {
    pthread_mutex_lock(&gpio_lock);
    bool v = ( (g->DIR & (1u << pin)) ? ((g->OUT >> pin) & 1u) : ((g->IN >> pin) & 1u) );
    pthread_mutex_unlock(&gpio_lock);
    return v;
}

static void msleep(long ms) {
    struct timespec req = { ms / 1000, (ms % 1000) * 1000000L };
    nanosleep(&req, NULL);
}

typedef struct { GPIO_Regs *g; uint8_t pin; int interval_ms; bool *stop_flag; } TimerArgs;

void *timer_thread(void *arg) {
    TimerArgs *t = (TimerArgs*)arg;
    while (!*(t->stop_flag)) {
        msleep(t->interval_ms);
        gpio_toggle_pin(t->g, t->pin);  // ISR-like toggle
    }
    return NULL;
}

int main(void) {
    GPIO_Regs *gpio = &SIM_GPIO;
    const uint8_t LED_PIN = 2;
    const int TOGGLE_MS = 400;

    bool stop = false;
    TimerArgs targs = { gpio, LED_PIN, TOGGLE_MS, &stop };

    gpio_set_dir(gpio, LED_PIN, true);

    pthread_t th;
    if (pthread_create(&th, NULL, timer_thread, &targs) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Main thread: print LED state every 250 ms for 5 seconds
    int cycles = 5000 / 250;
    for (int i = 0; i < cycles; ++i) {
        bool st = gpio_read_pin(gpio, LED_PIN);
        printf("[Main] Time %4d ms | LED=%s | OUT=0x%08" PRIX32 "\n",
               i*250, st ? "ON " : "OFF", gpio->OUT);
        msleep(250);
    }

    // stop timer
    stop = true;
    pthread_join(th, NULL);
    printf("Timer stopped.\n");
    return 0;
}
```

## Output
```bash
[Main] Time    0 ms | LED=OFF | OUT=0x00000000
[Main] Time  250 ms | LED=OFF | OUT=0x00000000
[Main] Time  500 ms | LED=ON  | OUT=0x00000004
[Main] Time  750 ms | LED=ON  | OUT=0x00000004
[Main] Time 1000 ms | LED=OFF | OUT=0x00000000
[Main] Time 1250 ms | LED=ON  | OUT=0x00000004
[Main] Time 1500 ms | LED=ON  | OUT=0x00000004
[Main] Time 1750 ms | LED=OFF | OUT=0x00000000
[Main] Time 2000 ms | LED=ON  | OUT=0x00000004
[Main] Time 2250 ms | LED=ON  | OUT=0x00000004
[Main] Time 2500 ms | LED=OFF | OUT=0x00000000
[Main] Time 2750 ms | LED=OFF | OUT=0x00000000
[Main] Time 3000 ms | LED=ON  | OUT=0x00000004
[Main] Time 3250 ms | LED=OFF | OUT=0x00000000
[Main] Time 3500 ms | LED=OFF | OUT=0x00000000
[Main] Time 3750 ms | LED=ON  | OUT=0x00000004
[Main] Time 4000 ms | LED=OFF | OUT=0x00000000
[Main] Time 4250 ms | LED=OFF | OUT=0x00000000
[Main] Time 4500 ms | LED=ON  | OUT=0x00000004
[Main] Time 4750 ms | LED=ON  | OUT=0x00000004
Timer stopped.
```

---

# Notes, ideas & extensions

* The code above intentionally models register semantics: writes only affect `OUT` if the `DIR` bit marks the pin as output. Inputs come from `IN`.
* You can simulate external inputs by writing the `IN` register (e.g., `SIM_GPIO.IN |= (1<<pin)`) to emulate a sensor or button press.
* To simulate electrical behaviour (pull-ups, tristate, open-drain), extend the register model with `PULLUP`, `DRIVE_TYPE`, etc.
* To unit test timing-sensitive logic deterministically, avoid real `nanosleep` and instead drive a simulated tick counter—call a `tick()` function that advances simulated time and triggers scheduled events.
* Use logs with timestamps or write to a CSV if you want to analyze the waveform.
* For more realistic microcontroller simulation, model an interrupt controller and peripheral registers; you can then exercise complete drivers without hardware.

---