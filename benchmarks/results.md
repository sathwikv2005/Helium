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
- Time: 2026-06-17 00:14:45

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 4.22x faster |
| Ruby (3.4.9) | 1.16x faster |
| Helium | 1.00x (baseline) |
| Python (3.11.2) | 1.27x slower |
| Perl (5.42.2) | 1.89x slower |

---

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.101760 | 0.001619 | 3.45x faster |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.247434 | 0.003031 | 1.42x faster |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.281574 | 0.003508 | 1.25x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.351259 | 0.017053 | 1.00x (baseline) |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 0.962055 | 0.005029 | 2.74x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.45x faster than Helium
- Ruby (3.4.9) is 1.42x faster than Helium
- Python (3.11.2) is 1.25x faster than Helium
- Perl (5.42.2) is 2.74x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.096174 | 0.004451 | 15.34x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.885560 | 0.008531 | 1.67x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 1.475108 | 0.023629 | 1.00x (baseline) |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.914187 | 0.043404 | 1.30x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.117098 | 0.014851 | 1.44x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 15.34x faster than Helium
- Ruby (3.4.9) is 1.67x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium
- Perl (5.42.2) is 1.44x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.160238 | 0.002743 | 10.38x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.901254 | 0.009337 | 1.84x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.662731 | 0.008129 | 1.00x (baseline) |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.670612 | 0.021518 | 1.00x slower |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.013688 | 0.031328 | 3.62x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 10.38x faster than Helium
- Ruby (3.4.9) is 1.84x faster than Helium
- Python (3.11.2) is 1.00x slower than Helium
- Perl (5.42.2) is 3.62x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.024999 | 0.000630 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.045126 | 0.000796 | 1.81x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048255 | 0.000834 | 1.93x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.072317 | 0.002571 | 2.89x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.145069 | 0.001787 | 5.80x slower |

### Helium comparison:
- Python (3.11.2) is 1.81x slower than Helium
- Perl (5.42.2) is 1.93x slower than Helium
- JavaScript (Node v26.3.0) is 2.89x slower than Helium
- Ruby (3.4.9) is 5.80x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.130040 | 0.003288 | 4.66x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.367368 | 0.004626 | 1.65x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.605821 | 0.019434 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 0.779564 | 0.007188 | 1.29x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.088545 | 0.021172 | 1.80x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 4.66x faster than Helium
- Ruby (3.4.9) is 1.65x faster than Helium
- Python (3.11.2) is 1.29x slower than Helium
- Perl (5.42.2) is 1.80x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.077591 | 0.003568 | 6.41x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.253003 | 0.006521 | 1.97x faster |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.459839 | 0.070496 | 1.08x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.497431 | 0.004088 | 1.00x (baseline) |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.857330 | 0.072794 | 1.72x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 6.41x faster than Helium
- Ruby (3.4.9) is 1.97x faster than Helium
- Perl (5.42.2) is 1.08x faster than Helium
- Python (3.11.2) is 1.72x slower than Helium

