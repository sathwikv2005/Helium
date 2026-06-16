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
- Time: 2026-06-17 03:24:33

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 3.61x faster |
| Helium | 1.00x (baseline) |
| Ruby (3.4.9) | 1.01x slower |
| Python (3.11.2) | 1.53x slower |
| Perl (5.42.2) | 2.21x slower |

---

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.096452 | 0.002140 | 2.72x faster |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.247743 | 0.002857 | 1.06x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.262059 | 0.002928 | 1.00x (baseline) |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.280476 | 0.003310 | 1.07x slower |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 0.969861 | 0.026877 | 3.70x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.72x faster than Helium
- Ruby (3.4.9) is 1.06x faster than Helium
- Python (3.11.2) is 1.07x slower than Helium
- Perl (5.42.2) is 3.70x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.098183 | 0.005248 | 14.05x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.884882 | 0.015345 | 1.56x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 1.379810 | 0.005540 | 1.00x (baseline) |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.936810 | 0.072138 | 1.40x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.104985 | 0.010032 | 1.53x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 14.05x faster than Helium
- Ruby (3.4.9) is 1.56x faster than Helium
- Python (3.11.2) is 1.40x slower than Helium
- Perl (5.42.2) is 1.53x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.158203 | 0.001535 | 8.35x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.897036 | 0.022816 | 1.47x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.321453 | 0.006457 | 1.00x (baseline) |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.663919 | 0.009830 | 1.26x slower |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 5.991210 | 0.035825 | 4.53x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 8.35x faster than Helium
- Ruby (3.4.9) is 1.47x faster than Helium
- Python (3.11.2) is 1.26x slower than Helium
- Perl (5.42.2) is 4.53x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.025023 | 0.002039 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.046357 | 0.005080 | 1.85x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048966 | 0.000676 | 1.96x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.072725 | 0.002353 | 2.91x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.147044 | 0.001841 | 5.88x slower |

### Helium comparison:
- Python (3.11.2) is 1.85x slower than Helium
- Perl (5.42.2) is 1.96x slower than Helium
- JavaScript (Node v26.3.0) is 2.91x slower than Helium
- Ruby (3.4.9) is 5.88x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.131199 | 0.001119 | 4.05x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.367660 | 0.032096 | 1.44x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.531004 | 0.007639 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 0.890718 | 0.046080 | 1.68x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.095245 | 0.050254 | 2.06x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 4.05x faster than Helium
- Ruby (3.4.9) is 1.44x faster than Helium
- Python (3.11.2) is 1.68x slower than Helium
- Perl (5.42.2) is 2.06x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.080376 | 0.001401 | 5.02x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.254288 | 0.011920 | 1.59x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.403764 | 0.003103 | 1.00x (baseline) |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.454579 | 0.009699 | 1.13x slower |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.893593 | 0.066504 | 2.21x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 5.02x faster than Helium
- Ruby (3.4.9) is 1.59x faster than Helium
- Perl (5.42.2) is 1.13x slower than Helium
- Python (3.11.2) is 2.21x slower than Helium

