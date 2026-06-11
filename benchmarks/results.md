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
- Time: 2026-06-12 04:24:36

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v20.19.1) | 4.62x faster |
| Ruby (3.4.9) | 1.31x faster |
| Helium | 1.00x (baseline) |
| Python (3.11.2) | 1.34x slower |
| Perl (5.42.2) | 1.69x slower |

---

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.114557 | 0.003678 | 3.93x faster |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.275047 | 0.003666 | 1.64x faster |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.373132 | 0.010651 | 1.21x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.450567 | 0.012683 | 1.00x (baseline) |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 1.087304 | 0.011909 | 2.41x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 3.93x faster than Helium
- Ruby (3.4.9) is 1.64x faster than Helium
- Python (3.11.2) is 1.21x faster than Helium
- Perl (5.42.2) is 2.41x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.092281 | 0.001142 | 18.25x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.914591 | 0.015502 | 1.84x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 1.683933 | 0.011744 | 1.00x (baseline) |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.993279 | 0.068628 | 1.18x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.130412 | 0.011854 | 1.27x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 18.25x faster than Helium
- Ruby (3.4.9) is 1.84x faster than Helium
- Python (3.11.2) is 1.18x slower than Helium
- Perl (5.42.2) is 1.27x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.175656 | 0.005066 | 10.24x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.900480 | 0.022006 | 2.00x faster |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.691176 | 0.026745 | 1.06x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.798218 | 0.032030 | 1.00x (baseline) |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.108901 | 0.072070 | 3.40x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 10.24x faster than Helium
- Ruby (3.4.9) is 2.00x faster than Helium
- Python (3.11.2) is 1.06x faster than Helium
- Perl (5.42.2) is 3.40x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.026897 | 0.000703 | 1.00x (baseline) |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.051376 | 0.001180 | 1.91x slower |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.071575 | 0.001547 | 2.66x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.075764 | 0.002353 | 2.82x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.155375 | 0.003403 | 5.78x slower |

### Helium comparison:
- Perl (5.42.2) is 1.91x slower than Helium
- Python (3.11.2) is 2.66x slower than Helium
- JavaScript (Node v20.19.1) is 2.82x slower than Helium
- Ruby (3.4.9) is 5.78x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.174425 | 0.008985 | 4.67x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.413563 | 0.003534 | 1.97x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.814429 | 0.012839 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.317895 | 0.048324 | 1.62x slower |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 1.472750 | 0.091753 | 1.81x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 4.67x faster than Helium
- Ruby (3.4.9) is 1.97x faster than Helium
- Perl (5.42.2) is 1.62x slower than Helium
- Python (3.11.2) is 1.81x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.081967 | 0.001421 | 7.99x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.260488 | 0.003212 | 2.51x faster |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.473465 | 0.007886 | 1.38x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.654819 | 0.009894 | 1.00x (baseline) |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.848664 | 0.035658 | 1.30x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 7.99x faster than Helium
- Ruby (3.4.9) is 2.51x faster than Helium
- Perl (5.42.2) is 1.38x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium

