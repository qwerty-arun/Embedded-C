# ✅ **What `extern` Means in C**

`extern` is used to **declare** a variable or function that is **defined in another file OR somewhere else in the same file**.

* It **does NOT allocate memory**.
* It only **declares** the variable so other files/functions know it exists.
* Actual memory is allocated where the variable is **defined** (without `extern`).

---

# 🔹 **1. Extern with Global Variables (Single File)**

### ✅ **Example 1 — extern declared before variable definition**

```c
#include <stdio.h>

extern int x;   // declaration (no memory allocated)
int x = 10;     // definition (memory allocated)

int main() {
    printf("x = %d\n", x);
    return 0;
}
```

### ✔ Output:

```
x = 10
```

---

# 🔹 **2. Extern When You Use Variable Before Definition**

```c
#include <stdio.h>

extern int a;

int main() {
    printf("%d\n", a);
    return 0;
}

int a = 25;
```

### ✔ Output:

```
25
```

Even though `a` is defined later, `extern` tells the compiler the variable exists somewhere.

---

# 🔹 **3. extern with Multiple C Files (MOST IMPORTANT USE-CASE)**

This is the **real purpose** of `extern`:
Sharing global variables across multiple `.c` files.

---

## 📁 File: **main.c**

```c
#include <stdio.h>

extern int counter;    // declaration

int main() {
    printf("Counter = %d\n", counter);
    return 0;
}
```

## 📁 File: **globals.c**

```c
int counter = 100;     // definition (memory allocated)
```

---

### ✔ How to compile:

```
gcc main.c globals.c -o output
```

### ✔ Output:

```
Counter = 100
```

---

# 🔹 **4. extern with Functions**

Functions are **extern by default**, but you can explicitly use it.

## 📁 File: **main.c**

```c
#include <stdio.h>

extern void greet();   // function declaration

int main() {
    greet();
    return 0;
}
```

## 📁 File: **greet.c**

```c
#include <stdio.h>

void greet() {
    printf("Hello from another file!\n");
}
```

### Compile:

```
gcc main.c greet.c -o prog
```

### Output:

```
Hello from another file!
```

---

# 🔹 **5. extern Inside Blocks (not common)**

```c
#include <stdio.h>

int x = 5;

int main() {
    {
        extern int x;  // refers to global x
        printf("%d\n", x);
    }
    return 0;
}
```

✔ Output:

```
5
```

---

# 🔹 **6. extern with const Variables**

`const` global variables have **internal linkage**.
To use them across files, you must declare them `extern`.

### 📁 File: **config.c**

```c
const int MAX_SPEED = 120;   // internal linkage
```

### 📁 File: **main.c**

```c
#include <stdio.h>

extern const int MAX_SPEED;  // must use extern

int main() {
    printf("%d\n", MAX_SPEED);
    return 0;
}
```

---

# 🔥 Summary Table

| Keyword              | Memory Allocated? | Scope  | Use Case                    |
| -------------------- | ----------------- | ------ | --------------------------- |
| `int x;`             | ✔ Yes             | Global | Definition                  |
| `extern int x;`      | ❌ No              | Global | Declaration in another file |
| `extern int x = 10;` | ❌ Invalid         | —      | Cannot define with extern   |

---


# 1) Extern with functions (shared state — counter across files)

Files:

```c
// counter.c  (definition)
#include <stdio.h>

int counter = 0;          // definition (storage)

void inc_counter(void) {
    counter++;
}

void print_counter(void) {
    printf("counter = %d\n", counter);
}
```

```c
// main.c  (uses extern)
#include <stdio.h>

extern int counter;           // declaration of global from another file
extern void inc_counter(void);
extern void print_counter(void);

int main(void) {
    inc_counter();
    inc_counter();
    print_counter();          // should print 2
    return 0;
}
```

Compile & run:

```
gcc main.c counter.c -o counter_prog
./counter_prog
```

Expected output:

```
counter = 2
```

# 2) Extern with arrays (large global array shared)

Files:

```c
// data.c  (definition)
int values[] = {10, 20, 30, 40};   // definition
int values_len = sizeof(values)/sizeof(values[0]);
```

```c
// sum.c  (uses extern to read array)
#include <stdio.h>

extern int values[];       // declaration of array
extern int values_len;

int sum_values(void) {
    int s = 0;
    for (int i = 0; i < values_len; ++i) s += values[i];
    return s;
}
```

```c
// main.c
#include <stdio.h>

extern int sum_values(void);

int main(void) {
    printf("sum = %d\n", sum_values());   // expect 100
    return 0;
}
```

Compile & run:

```
gcc main.c sum.c data.c -o sum_prog
./sum_prog
```

Expected output:

```
sum = 100
```

# 3) Extern with structures (shared config)

Files:

```c
// config.c  (definition)
#include <stdio.h>

typedef struct {
    int width;
    int height;
    const char *title;
} AppConfig;

AppConfig app_config = {800, 600, "MyApp"};
```

```c
// ui.c  (uses extern)
#include <stdio.h>

typedef struct {
    int width;
    int height;
    const char *title;
} AppConfig;

extern AppConfig app_config;

void show_config(void) {
    printf("%s: %dx%d\n", app_config.title, app_config.width, app_config.height);
}
```

```c
// main.c
extern void show_config(void);

int main(void) {
    show_config();   // prints "MyApp: 800x600"
    return 0;
}
```

Compile:

```
gcc main.c ui.c config.c -o app
./app
```

Output:

```
MyApp: 800x600
```

# 4) Proper header-file pattern (best practice)

Use a header to declare externs and share types.

Files:

```c
// config.h
#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int width;
    int height;
    const char *title;
} AppConfig;

extern AppConfig app_config;   // extern declaration for other files

#endif // CONFIG_H
```

```c
// config.c
#include "config.h"

AppConfig app_config = {1024, 768, "Header Example"}; // definition
```

```c
// main.c
#include <stdio.h>
#include "config.h"

int main(void) {
    printf("%s -> %dx%d\n", app_config.title, app_config.width, app_config.height);
    return 0;
}
```

Compile:

```
gcc main.c config.c -o hdr_demo
./hdr_demo
```

Output:

```
Header Example -> 1024x768
```

**Why use a header?** Single source of truth for the type and extern declaration; prevents mismatched declarations and duplication.

# 5) Example: extern with `const` and linkage gotcha

`const` globals have internal linkage by default in C (like `static`), so you must explicitly define them with `extern` in the definition if you want external linkage.

```c
// conf.c
extern const int MAX_CONN = 10;  // definition with extern -> external linkage
```

```c
// main.c
#include <stdio.h>
extern const int MAX_CONN;
int main(void) { printf("%d\n", MAX_CONN); return 0; }
```

If you instead write `const int MAX_CONN = 10;` in `conf.c` and try to `extern` it in another translation unit, the linker may not find it (because of internal linkage). Safer: use the header `extern const int MAX_CONN;` and in exactly one `.c` define `const int MAX_CONN = ...;` but ensure compiler semantics — using `extern` on the definition makes intent explicit.

# 6) Common mistakes & compiler errors (and fixes)

* **Multiple definitions linker error (`multiple definition of 'x'`)**
  Cause: defining the same global in more than one `.c` (e.g., placing `int x = 0;` in a header and including header in multiple `.c`).
  Fix: Put `extern int x;` in header, and `int x = 0;` in exactly one `.c`.

* **Undefined reference at link time (`undefined reference to 'x'`)**
  Cause: declared `extern int x;` but never defined `int x;` in any compiled file.
  Fix: Add the definition in one .c and compile/link it.

* **Wrong type between declaration and definition**
  Cause: mismatched types/signatures in header and definition.
  Fix: keep one header with the correct declaration and include it everywhere.

* **Expecting `extern` to initialize memory**
  `extern int x = 5;` is a definition (it both declares and defines) — avoid confusing uses. Prefer either `int x = 5;` in one file or `extern int x;` in headers/other files.

# 7) A compact real-world example: plugin-style increment and print

`plugin.c` defines functions and state; `main.c` calls them via `extern`. This is just a merge of earlier examples but demonstrates how modules interact.

# 8) Quick checklist when using extern

* Put `extern` declarations in headers (no initialization there).
* Define (no `extern`) in exactly one `.c`.
* Include the header wherever you use the variable/function.
* Use `gcc file1.c file2.c -o prog` to link everything in one step.
* Use `nm` or `objdump -t` to inspect symbol table when debugging link errors.

---