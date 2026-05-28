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
- Time: 2026-05-28 06:48:08

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v20.19.1) | 4.87x faster |
| Ruby (3.4.9) | 1.13x faster |
| Helium | 1.00x (baseline) |
| Python (3.11.2) | 1.37x slower |
| Perl (5.42.2) | 1.57x slower |

---

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.092013 | 0.003106 | 18.07x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.881282 | 0.005206 | 1.89x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 1.662416 | 0.010887 | 1.00x (baseline) |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.944670 | 0.049605 | 1.17x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.094395 | 0.013064 | 1.26x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 18.07x faster than Helium
- Ruby (3.4.9) is 1.89x faster than Helium
- Python (3.11.2) is 1.17x slower than Helium
- Perl (5.42.2) is 1.26x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.159329 | 0.007614 | 10.92x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.885015 | 0.005847 | 1.97x faster |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.677910 | 0.015736 | 1.04x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.740047 | 0.007794 | 1.00x (baseline) |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.045096 | 0.050558 | 3.47x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 10.92x faster than Helium
- Ruby (3.4.9) is 1.97x faster than Helium
- Python (3.11.2) is 1.04x faster than Helium
- Perl (5.42.2) is 3.47x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.027171 | 0.001373 | 1.00x (baseline) |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.051632 | 0.001344 | 1.90x slower |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.068279 | 0.001507 | 2.51x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.075134 | 0.002653 | 2.77x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.156342 | 0.009846 | 5.75x slower |

### Helium comparison:
- Perl (5.42.2) is 1.90x slower than Helium
- Python (3.11.2) is 2.51x slower than Helium
- JavaScript (Node v20.19.1) is 2.77x slower than Helium
- Ruby (3.4.9) is 5.75x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.082743 | 0.002938 | 7.86x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.256615 | 0.013367 | 2.53x faster |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.469550 | 0.018882 | 1.38x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.649956 | 0.021148 | 1.00x (baseline) |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.801460 | 0.022633 | 1.23x slower |

### Helium comparison:
- JavaScript (Node v20.19.1) is 7.86x faster than Helium
- Ruby (3.4.9) is 2.53x faster than Helium
- Perl (5.42.2) is 1.38x faster than Helium
- Python (3.11.2) is 1.23x slower than Helium

