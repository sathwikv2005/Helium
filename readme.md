# Helium

**Helium** is a lightweight programming language featuring a custom bytecode virtual machine, automatic garbage collection, and a minimal syntax designed for simplicity and performance.

**Light as gas. Fast as lightning.**

---

## Overview

Helium is a programming language built from scratch to explore how programming languages work internally.  
It focuses on keeping the language small, simple, and fast while implementing core runtime features such as a virtual machine and automatic memory management.

The project is heavily inspired by the book _Crafting Interpreters_ and serves as a learning project for language implementation.

---

## Examples

```js
// fib.he
function fib(n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

print fib(10); //55
```

```js
// pi.he
var n = 10000000;
var step = 1.0 / n;
var sum = 0.0;

var i = 0;
while (i < n) {
    var x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
    i = i + 1;
}

var pi = sum * step;
print pi; //3.14159265358973
```

---

## Building

### Windows

Use the provided build script:

```bat
build.bat
```

For a debug build:

```bat
debug_build.bat
```

### Manual Build

```bash
cmake -B build -G "MinGW Makefiles"
cmake --build build --target helium
```

For a debug build:

```bash
cmake -B build -G "MinGW Makefiles"
cmake --build build --target debug
```

---

## Running

Start the REPL:

```bash
./helium
```

Run a script:

```bash
./helium program.he
```

---

## Testing

Run the test suite:

```bat
test.bat
```

The test suite can also be run directly with Python:

```bash
python tools/tester.py
```

---

## Benchmarks

> Helium currently outperforms Ruby, Python, and Perl across the benchmark suite. Startup time is particularly strong, with Helium launching faster than all tested languages.

Performance benchmark results comparing Helium with other scripting languages can be found [here](benchmarks/results.md).
