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
- Time: 2026-06-07 21:26:04

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v20.19.1) | 4.37x faster |
| Ruby (3.4.9) | 1.07x faster |
| Helium | 1.00x (baseline) |
| Python (3.11.2) | 1.44x slower |
| Perl (5.42.2) | 1.62x slower |

---

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.101127 | 0.002571 | 17.85x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.956859 | 0.023936 | 1.89x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 1.805096 | 0.042269 | 1.00x (baseline) |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 2.162942 | 0.112374 | 1.20x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.290999 | 0.082423 | 1.27x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 17.85x faster than Helium
- Ruby (3.4.9) is 1.89x faster than Helium
- Python (3.11.2) is 1.20x slower than Helium
- Perl (5.42.2) is 1.27x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.224093 | 0.050374 | 8.22x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.993709 | 0.032538 | 1.85x faster |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.784319 | 0.032100 | 1.03x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.841464 | 0.040315 | 1.00x (baseline) |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.429229 | 0.108411 | 3.49x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 8.22x faster than Helium
- Ruby (3.4.9) is 1.85x faster than Helium
- Python (3.11.2) is 1.03x faster than Helium
- Perl (5.42.2) is 3.49x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.029124 | 0.000591 | 1.00x (baseline) |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.058312 | 0.005352 | 2.00x slower |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.081809 | 0.002340 | 2.81x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.089214 | 0.007789 | 3.06x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.181719 | 0.007023 | 6.24x slower |

### Helium comparison:
- Perl (5.42.2) is 2.00x slower than Helium
- Python (3.11.2) is 2.81x slower than Helium
- JavaScript (Node v20.19.1) is 3.06x slower than Helium
- Ruby (3.4.9) is 6.24x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.091222 | 0.002620 | 7.58x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.295268 | 0.010984 | 2.34x faster |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.530766 | 0.030268 | 1.30x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.691641 | 0.022458 | 1.00x (baseline) |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.900588 | 0.074519 | 1.30x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 7.58x faster than Helium
- Ruby (3.4.9) is 2.34x faster than Helium
- Perl (5.42.2) is 1.30x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium

