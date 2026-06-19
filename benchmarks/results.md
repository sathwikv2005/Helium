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
- Time: 2026-06-19 21:01:57

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 2.48x faster |
| Helium | 1.00x (baseline) |
| Ruby (3.4.9) | 1.48x slower |
| Python (3.11.2) | 1.84x slower |
| Perl (5.42.2) | 2.37x slower |

---

## array-sum

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./array-sum/sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093856 | 0.003199 | 1.27x faster |
| <a href="./array-sum/sum.he" target="_blank">Helium</a> | 0.119363 | 0.003032 | 1.00x (baseline) |
| <a href="./array-sum/sum.py" target="_blank">Python (3.11.2)</a> | 0.225939 | 0.005704 | 1.89x slower |
| <a href="./array-sum/sum.pl" target="_blank">Perl (5.42.2)</a> | 0.228935 | 0.001389 | 1.92x slower |
| <a href="./array-sum/sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.348458 | 0.013377 | 2.92x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.27x faster than Helium
- Python (3.11.2) is 1.89x slower than Helium
- Perl (5.42.2) is 1.92x slower than Helium
- Ruby (3.4.9) is 2.92x slower than Helium

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099597 | 0.011326 | 2.44x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.242741 | 0.009198 | 1.00x (baseline) |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.247578 | 0.004998 | 1.02x slower |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.289926 | 0.006110 | 1.19x slower |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 0.970182 | 0.014811 | 4.00x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.44x faster than Helium
- Ruby (3.4.9) is 1.02x slower than Helium
- Python (3.11.2) is 1.19x slower than Helium
- Perl (5.42.2) is 4.00x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.086739 | 0.005343 | 8.54x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 0.740944 | 0.015742 | 1.00x (baseline) |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.879630 | 0.010708 | 1.19x slower |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.943347 | 0.090564 | 2.62x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.103575 | 0.026837 | 2.84x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 8.54x faster than Helium
- Ruby (3.4.9) is 1.19x slower than Helium
- Python (3.11.2) is 2.62x slower than Helium
- Perl (5.42.2) is 2.84x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.160001 | 0.003662 | 7.65x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.882000 | 0.006867 | 1.39x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.223986 | 0.020903 | 1.00x (baseline) |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.680429 | 0.038997 | 1.37x slower |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.009357 | 0.068025 | 4.91x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 7.65x faster than Helium
- Ruby (3.4.9) is 1.39x faster than Helium
- Python (3.11.2) is 1.37x slower than Helium
- Perl (5.42.2) is 4.91x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.023907 | 0.000922 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.045760 | 0.001360 | 1.91x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048740 | 0.001040 | 2.04x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.073864 | 0.002057 | 3.09x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.146524 | 0.001451 | 6.13x slower |

### Helium comparison:
- Python (3.11.2) is 1.91x slower than Helium
- Perl (5.42.2) is 2.04x slower than Helium
- JavaScript (Node v26.3.0) is 3.09x slower than Helium
- Ruby (3.4.9) is 6.13x slower than Helium

## matrix

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./matrix/matrix.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.089847 | 0.005784 | 3.02x faster |
| <a href="./matrix/matrix.he" target="_blank">Helium</a> | 0.271720 | 0.047847 | 1.00x (baseline) |
| <a href="./matrix/matrix.rb" target="_blank">Ruby (3.4.9)</a> | 0.390396 | 0.009751 | 1.44x slower |
| <a href="./matrix/matrix.pl" target="_blank">Perl (5.42.2)</a> | 0.504534 | 0.018814 | 1.86x slower |
| <a href="./matrix/matrix.py" target="_blank">Python (3.11.2)</a> | 0.511054 | 0.028325 | 1.88x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.02x faster than Helium
- Ruby (3.4.9) is 1.44x slower than Helium
- Perl (5.42.2) is 1.86x slower than Helium
- Python (3.11.2) is 1.88x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.131283 | 0.002273 | 3.71x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.366083 | 0.003378 | 1.33x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.486459 | 0.010556 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 0.789445 | 0.009081 | 1.62x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.077899 | 0.012821 | 2.22x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.71x faster than Helium
- Ruby (3.4.9) is 1.33x faster than Helium
- Python (3.11.2) is 1.62x slower than Helium
- Perl (5.42.2) is 2.22x slower than Helium

## sieve

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve/sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.104581 | 0.002329 | 2.04x faster |
| <a href="./sieve/sieve.he" target="_blank">Helium</a> | 0.213835 | 0.002920 | 1.00x (baseline) |
| <a href="./sieve/sieve.py" target="_blank">Python (3.11.2)</a> | 0.333681 | 0.020522 | 1.56x slower |
| <a href="./sieve/sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.336831 | 0.006400 | 1.58x slower |
| <a href="./sieve/sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.453912 | 0.010120 | 2.12x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.04x faster than Helium
- Python (3.11.2) is 1.56x slower than Helium
- Ruby (3.4.9) is 1.58x slower than Helium
- Perl (5.42.2) is 2.12x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.078433 | 0.001173 | 3.67x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.251994 | 0.020598 | 1.14x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.288108 | 0.010043 | 1.00x (baseline) |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.459264 | 0.013767 | 1.59x slower |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.835090 | 0.056183 | 2.90x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.67x faster than Helium
- Ruby (3.4.9) is 1.14x faster than Helium
- Perl (5.42.2) is 1.59x slower than Helium
- Python (3.11.2) is 2.90x slower than Helium

## sqrt

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt/sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.082034 | 0.006645 | 1.57x faster |
| <a href="./sqrt/sqrt.he" target="_blank">Helium</a> | 0.129075 | 0.004516 | 1.00x (baseline) |
| <a href="./sqrt/sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.238529 | 0.002979 | 1.85x slower |
| <a href="./sqrt/sqrt.py" target="_blank">Python (3.11.2)</a> | 0.268735 | 0.010753 | 2.08x slower |
| <a href="./sqrt/sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.283584 | 0.016376 | 2.20x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.57x faster than Helium
- Perl (5.42.2) is 1.85x slower than Helium
- Python (3.11.2) is 2.08x slower than Helium
- Ruby (3.4.9) is 2.20x slower than Helium

