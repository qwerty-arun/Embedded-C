
# ⭐ 1. GPIO (General-Purpose Input/Output)

### **What GPIO is**

GPIO pins are the MCU’s way of interacting with the outside world: LEDs, buttons, sensors, relays, motors — everything starts here.

### **Key Concepts**

* **Direction:**

  * `Input` → read pin voltage
  * `Output` → drive pin high/low
* **Pull-up / Pull-down:**

  * Internal resistors that define a known level for floating inputs.
  * e.g., a button uses pull-up so unpressed = logic HIGH.
* **Drive Strength:** how much current the pin can source/sink (usually 5–20 mA).
* **Alternate Functions (AF):**
  GPIO pins can turn into UART TX, SPI CLK, I²C SDA, etc.

### **Typical Register Settings**

1. Mode register → input/output/AF/analog
2. Pull-up/pull-down
3. Output type → push-pull / open-drain
4. Speed → low/medium/high drive speed

---

# ⭐ 2. Timers (General-Purpose Timers / PWM Timers)

### **What Timers are**

Timers are hardware counters driven by the MCU clock. They allow **precise time measurement**, **delays**, **PWM generation**, and **periodic interrupts**.

### **How Timers Work**

A timer consists of:

* **Clock Input** → from system clock
* **Prescaler** → divides clock to get slower tick
* **Counter** → increments every tick
* **Auto-Reload Register (ARR)** → decides when counter resets
* **Compare Registers (CCR)** → trigger events/PWM when counter = CCR

### **Timer Use Cases**

* **Delay / periodic tasks:** e.g., 1 ms interrupt for RTOS tick
* **PWM:** motor control, LED brightness, servo signals
* **Input capture:** measure frequency, pulse width
* **Output compare:** generate precise square waves
* **Event timing:** measure how long something takes

### **Example**

If timer clock = 72 MHz
Prescaler = 7200 → timer ticks at 10 kHz
ARR = 10,000 → overflow every 1 second

---

# ⭐ 3. UART (Universal Asynchronous Receiver/Transmitter)

### **What UART is**

UART is a **simple, asynchronous, point-to-point serial communication** protocol. It sends bits in a timed sequence — no clock pin.

### **Frame Format**

```
Start bit (0)
Data bits (usually 8)
Optional parity bit
Stop bit (1)
```

### **Why It’s Called Asynchronous**

No shared clock.
Both sides must **agree on baud rate** (9600, 115200, etc.).
If baud mismatches → garbage characters.

### **Key UART Terms**

* **Baud Rate Generator:** timer-like divider for bit timing
* **TX** → transmit
* **RX** → receive
* **TX/RX buffers & interrupts:** for non-blocking communication
* **DMA support:** fast transfers

### **Use Cases**

* Debug printing (`printf` to serial monitor)
* Communication with modules: GPS, GSM, ESP8266
* Bootloaders
* PC ↔ MCU communication

---

# ⭐ 4. I²C (Inter-Integrated Circuit)

### **What I²C is**

A **two-wire**, synchronous, multi-master, multi-slave serial bus:

* **SDA** → data
* **SCL** → clock

Both wires are **open-drain** → need external pull-ups.

### **Characteristics**

* Addresses devices by 7-bit or 10-bit addresses
* Uses **ACK/NACK** for handshaking
* Speeds:

  * Standard: 100 kHz
  * Fast: 400 kHz
  * Fast+ : 1 MHz
  * High Speed: 3.4 MHz

### **I²C Transaction Overview**

1. **Start Condition**
2. **Send Slave Address + R/W bit**
3. **Wait for ACK**
4. **Send/receive bytes (each followed by ACK)**
5. **Stop Condition**

### **Use Cases**

* Sensors: MPU6050, BMP280, OLED display
* EEPROMs
* RTC modules
* Low-speed configuration buses

### **Pros**

* Only 2 wires for many devices
* Addressed communication

### **Cons**

* Slower than SPI
* Requires pull-up resistors
* Somewhat complex protocol state machine

---

# ⭐ 5. SPI (Serial Peripheral Interface)


### **What SPI is**

SPI is a **fast, synchronous, full-duplex** serial communication protocol.

### **Wires**

* **MOSI** – Master Out Slave In
* **MISO** – Master In Slave Out
* **SCK** – Clock
* **SS/CS** – Chip Select (one per slave)

### **Key Features**

* VERY high speed: 1–50+ MHz
* Full duplex (send and receive simultaneously)
* No addressing → each slave needs its own CS pin
* Four modes depending on clock polarity (CPOL) and phase (CPHA)

### **SPI Pros**

* Fastest common MCU protocol
* Simple hardware
* Ideal for streaming data

### **SPI Cons**

* More wires than I²C
* Limited number of slaves unless you add decoders

### **Use Cases**

* Flash memory chips
* Displays (TFT, OLED)
* SD cards
* High-speed sensors
* Motor drivers

---

# 🧠 Summary Table

| Feature   | GPIO          | Timer                  | UART           | I²C                     | SPI              |
| --------- | ------------- | ---------------------- | -------------- | ----------------------- | ---------------- |
| Purpose   | Basic IO      | Time measurement & PWM | Serial async   | Serial sync multi-slave | Fast sync serial |
| Wires     | Single pin    | Internal               | 2 (TX,RX)      | 2                       | 3+               |
| Speed     | Instant       | Depends on clock       | ~115 k         | 100k–3.4M               | 1M–50M           |
| Clock?    | No            | Internal               | No             | Yes                     | Yes              |
| Use Cases | LEDs, buttons | PWM, delays            | Debug, modules | Sensors                 | Displays, memory |

---
