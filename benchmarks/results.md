# Global Benchmark Results

## Benchmark Methodology

- Each benchmark is executed multiple times to reduce noise.
- Warmup runs: 2
- Measured runs: 10
- Median execution time is used for comparison.
- Output is suppressed to avoid affecting timings.
- Each program runs as a separate process.
- C programs are compiled with `-O2` optimization.

## System Information

- OS: Windows 11
- CPU: AMD Ryzen 7 4800H with Radeon Graphics
- RAM: 15.42GB
- Time: 2026-05-01 12:22:15

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v20.19.1) | 5.06x faster |
| Ruby (3.4.9) | 1.10x faster |
| Helium | 1.00x (baseline) |
| Python (3.11.2) | 1.36x slower |
| Perl (5.42.2) | 1.54x slower |

---

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.086253 | 0.002059 | 19.28x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.889996 | 0.015846 | 1.87x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 1.663118 | 0.008472 | 1.00x (baseline) |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.958210 | 0.071368 | 1.18x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.113200 | 0.020348 | 1.27x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 19.28x faster than Helium
- Ruby (3.4.9) is 1.87x faster than Helium
- Python (3.11.2) is 1.18x slower than Helium
- Perl (5.42.2) is 1.27x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.158774 | 0.001992 | 11.28x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.893956 | 0.016700 | 2.00x faster |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.661509 | 0.021084 | 1.08x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.790530 | 0.009120 | 1.00x (baseline) |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.070506 | 0.044750 | 3.39x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 11.28x faster than Helium
- Ruby (3.4.9) is 2.00x faster than Helium
- Python (3.11.2) is 1.08x faster than Helium
- Perl (5.42.2) is 3.39x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.022585 | 0.001144 | 1.00x (baseline) |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.046196 | 0.001582 | 2.05x slower |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.061529 | 0.002772 | 2.72x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.070485 | 0.001919 | 3.12x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.162125 | 0.008262 | 7.18x slower |

### Helium comparison:
- Perl (5.42.2) is 2.05x slower than Helium
- Python (3.11.2) is 2.72x slower than Helium
- JavaScript (Node v20.19.1) is 3.12x slower than Helium
- Ruby (3.4.9) is 7.18x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.074984 | 0.001078 | 9.40x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.255670 | 0.005988 | 2.76x faster |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.453494 | 0.006631 | 1.55x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.704970 | 0.009512 | 1.00x (baseline) |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.801412 | 0.045826 | 1.14x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 9.40x faster than Helium
- Ruby (3.4.9) is 2.76x faster than Helium
- Perl (5.42.2) is 1.55x faster than Helium
- Python (3.11.2) is 1.14x slower than Helium

