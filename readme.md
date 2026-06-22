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
//word frequency
var text = "red blue red green blue red";
var words = text.split(" ");

var counts = {};

var i = 0;
while (i < words.length()) {
    var word = words[i];

    if (counts[word] == null) {
        counts[word] = 1;
    } else {
        counts[word]++;
    }

    i++;
}

print counts["red"];   // 3
print counts["blue"];  // 2
```

```js
// Object-oriented programming
class Counter {
    init(start) {
        this.value = start;
    }

    increment() {
        this.value++;
    }

    get() {
        return this.value;
    }
}

var counter = Counter(10);

counter.increment();
counter.increment();

print counter.get(); // 12
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
