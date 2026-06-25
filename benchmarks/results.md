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
- Time: 2026-06-25 18:57:04

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 2.28x faster |
| Helium | 1.00x (baseline) |
| Ruby (3.4.9) | 1.46x slower |
| Python (3.12.11) | 2.13x slower |
| Perl (5.42.2) | 2.25x slower |

---

## array-sum

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./array-sum/sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093878 | 0.006360 | 1.50x faster |
| <a href="./array-sum/sum.he" target="_blank">Helium</a> | 0.141040 | 0.005238 | 1.00x (baseline) |
| <a href="./array-sum/sum.pl" target="_blank">Perl (5.42.2)</a> | 0.248553 | 0.007417 | 1.76x slower |
| <a href="./array-sum/sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.353240 | 0.008835 | 2.50x slower |
| <a href="./array-sum/sum.py" target="_blank">Python (3.12.11)</a> | 0.394820 | 0.014132 | 2.80x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.50x faster than Helium
- Perl (5.42.2) is 1.76x slower than Helium
- Ruby (3.4.9) is 2.50x slower than Helium
- Python (3.12.11) is 2.80x slower than Helium

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.108177 | 0.014762 | 2.39x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.258815 | 0.011693 | 1.00x (baseline) |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.300580 | 0.011291 | 1.16x slower |
| <a href="./b-tree/tree.py" target="_blank">Python (3.12.11)</a> | 0.330939 | 0.027551 | 1.28x slower |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 1.105921 | 0.091767 | 4.27x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.39x faster than Helium
- Ruby (3.4.9) is 1.16x slower than Helium
- Python (3.12.11) is 1.28x slower than Helium
- Perl (5.42.2) is 4.27x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099078 | 0.003300 | 9.58x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.923893 | 0.018067 | 1.03x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 0.949483 | 0.011640 | 1.00x (baseline) |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.357390 | 0.033631 | 2.48x slower |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.12.11)</a> | 3.604538 | 0.076443 | 3.80x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 9.58x faster than Helium
- Ruby (3.4.9) is 1.03x faster than Helium
- Perl (5.42.2) is 2.48x slower than Helium
- Python (3.12.11) is 3.80x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.161885 | 0.004260 | 7.79x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.900740 | 0.018643 | 1.40x faster |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.12.11)</a> | 1.200102 | 0.021507 | 1.05x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.260681 | 0.035789 | 1.00x (baseline) |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 5.986817 | 0.044561 | 4.75x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 7.79x faster than Helium
- Ruby (3.4.9) is 1.40x faster than Helium
- Python (3.12.11) is 1.05x faster than Helium
- Perl (5.42.2) is 4.75x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.022857 | 0.000555 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.12.11)</a> | 0.049840 | 0.001433 | 2.18x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.051514 | 0.003976 | 2.25x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.076782 | 0.006444 | 3.36x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.149598 | 0.005943 | 6.55x slower |

### Helium comparison:
- Python (3.12.11) is 2.18x slower than Helium
- Perl (5.42.2) is 2.25x slower than Helium
- JavaScript (Node v26.3.0) is 3.36x slower than Helium
- Ruby (3.4.9) is 6.55x slower than Helium

## matrix

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./matrix/matrix.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.086946 | 0.002153 | 3.17x faster |
| <a href="./matrix/matrix.he" target="_blank">Helium</a> | 0.275865 | 0.008286 | 1.00x (baseline) |
| <a href="./matrix/matrix.rb" target="_blank">Ruby (3.4.9)</a> | 0.388915 | 0.004881 | 1.41x slower |
| <a href="./matrix/matrix.pl" target="_blank">Perl (5.42.2)</a> | 0.457513 | 0.010542 | 1.66x slower |
| <a href="./matrix/matrix.py" target="_blank">Python (3.12.11)</a> | 0.799956 | 0.021527 | 2.90x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.17x faster than Helium
- Ruby (3.4.9) is 1.41x slower than Helium
- Perl (5.42.2) is 1.66x slower than Helium
- Python (3.12.11) is 2.90x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.127571 | 0.001750 | 3.72x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.362594 | 0.005842 | 1.31x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.475027 | 0.009540 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.12.11)</a> | 1.053393 | 0.009606 | 2.22x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.068290 | 0.008220 | 2.25x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.72x faster than Helium
- Ruby (3.4.9) is 1.31x faster than Helium
- Python (3.12.11) is 2.22x slower than Helium
- Perl (5.42.2) is 2.25x slower than Helium

## sieve

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve/sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.100431 | 0.001387 | 2.17x faster |
| <a href="./sieve/sieve.he" target="_blank">Helium</a> | 0.218172 | 0.003212 | 1.00x (baseline) |
| <a href="./sieve/sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.330016 | 0.005800 | 1.51x slower |
| <a href="./sieve/sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.450743 | 0.007226 | 2.07x slower |
| <a href="./sieve/sieve.py" target="_blank">Python (3.12.11)</a> | 0.548667 | 0.014601 | 2.51x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.17x faster than Helium
- Ruby (3.4.9) is 1.51x slower than Helium
- Perl (5.42.2) is 2.07x slower than Helium
- Python (3.12.11) is 2.51x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.076323 | 0.002325 | 4.21x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.296767 | 0.033083 | 1.08x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.321564 | 0.005400 | 1.00x (baseline) |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.455472 | 0.013526 | 1.42x slower |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.12.11)</a> | 1.018415 | 0.049353 | 3.17x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 4.21x faster than Helium
- Ruby (3.4.9) is 1.08x faster than Helium
- Perl (5.42.2) is 1.42x slower than Helium
- Python (3.12.11) is 3.17x slower than Helium

## sqrt

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt/sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093182 | 0.015219 | 1.44x faster |
| <a href="./sqrt/sqrt.he" target="_blank">Helium</a> | 0.133921 | 0.003629 | 1.00x (baseline) |
| <a href="./sqrt/sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.234532 | 0.006113 | 1.75x slower |
| <a href="./sqrt/sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.278250 | 0.003217 | 2.08x slower |
| <a href="./sqrt/sqrt.py" target="_blank">Python (3.12.11)</a> | 0.358106 | 0.008146 | 2.67x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.44x faster than Helium
- Perl (5.42.2) is 1.75x slower than Helium
- Ruby (3.4.9) is 2.08x slower than Helium
- Python (3.12.11) is 2.67x slower than Helium

## word-freq

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./word-freq/freq.he" target="_blank">Helium</a> | 0.770612 | 0.043896 | 1.00x (baseline) |
| <a href="./word-freq/freq.py" target="_blank">Python (3.12.11)</a> | 0.819217 | 0.006242 | 1.06x slower |
| <a href="./word-freq/freq.js" target="_blank">JavaScript (Node v26.3.0)</a> | 1.085323 | 0.005907 | 1.41x slower |
| <a href="./word-freq/freq.rb" target="_blank">Ruby (3.4.9)</a> | 1.224373 | 0.003207 | 1.59x slower |
| <a href="./word-freq/freq.pl" target="_blank">Perl (5.42.2)</a> | 1.485137 | 0.023948 | 1.93x slower |

### Helium comparison:
- Python (3.12.11) is 1.06x slower than Helium
- JavaScript (Node v26.3.0) is 1.41x slower than Helium
- Ruby (3.4.9) is 1.59x slower than Helium
- Perl (5.42.2) is 1.93x slower than Helium

