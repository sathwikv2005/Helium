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
- Time: 2026-06-24 01:16:59

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 2.09x faster |
| Helium | 1.00x (baseline) |
| Ruby (3.4.9) | 1.60x slower |
| Python (3.11.2) | 1.81x slower |
| Perl (5.42.2) | 2.42x slower |

---

## array-sum

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./array-sum/sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.102668 | 0.019067 | 1.23x faster |
| <a href="./array-sum/sum.he" target="_blank">Helium</a> | 0.126168 | 0.004822 | 1.00x (baseline) |
| <a href="./array-sum/sum.py" target="_blank">Python (3.11.2)</a> | 0.230242 | 0.002938 | 1.82x slower |
| <a href="./array-sum/sum.pl" target="_blank">Perl (5.42.2)</a> | 0.233406 | 0.016550 | 1.85x slower |
| <a href="./array-sum/sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.353018 | 0.020128 | 2.80x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.23x faster than Helium
- Python (3.11.2) is 1.82x slower than Helium
- Perl (5.42.2) is 1.85x slower than Helium
- Ruby (3.4.9) is 2.80x slower than Helium

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099502 | 0.004194 | 2.51x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.249750 | 0.014090 | 1.00x (baseline) |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.266289 | 0.011776 | 1.07x slower |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.292103 | 0.004415 | 1.17x slower |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 0.978354 | 0.014830 | 3.92x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.51x faster than Helium
- Ruby (3.4.9) is 1.07x slower than Helium
- Python (3.11.2) is 1.17x slower than Helium
- Perl (5.42.2) is 3.92x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.088462 | 0.001306 | 7.66x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 0.677322 | 0.016002 | 1.00x (baseline) |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.884048 | 0.008440 | 1.31x slower |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.912902 | 0.059005 | 2.82x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.104410 | 0.014818 | 3.11x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 7.66x faster than Helium
- Ruby (3.4.9) is 1.31x slower than Helium
- Python (3.11.2) is 2.82x slower than Helium
- Perl (5.42.2) is 3.11x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.162350 | 0.011141 | 7.17x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.902243 | 0.044107 | 1.29x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.163597 | 0.012462 | 1.00x (baseline) |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.680821 | 0.019684 | 1.44x slower |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 5.973498 | 0.028061 | 5.13x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 7.17x faster than Helium
- Ruby (3.4.9) is 1.29x faster than Helium
- Python (3.11.2) is 1.44x slower than Helium
- Perl (5.42.2) is 5.13x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.024083 | 0.000655 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.044948 | 0.001670 | 1.87x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.049455 | 0.002471 | 2.05x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.073823 | 0.002002 | 3.07x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.159578 | 0.009906 | 6.63x slower |

### Helium comparison:
- Python (3.11.2) is 1.87x slower than Helium
- Perl (5.42.2) is 2.05x slower than Helium
- JavaScript (Node v26.3.0) is 3.07x slower than Helium
- Ruby (3.4.9) is 6.63x slower than Helium

## matrix

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./matrix/matrix.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.088420 | 0.002258 | 2.74x faster |
| <a href="./matrix/matrix.he" target="_blank">Helium</a> | 0.242260 | 0.004491 | 1.00x (baseline) |
| <a href="./matrix/matrix.rb" target="_blank">Ruby (3.4.9)</a> | 0.390920 | 0.055924 | 1.61x slower |
| <a href="./matrix/matrix.pl" target="_blank">Perl (5.42.2)</a> | 0.505818 | 0.006319 | 2.09x slower |
| <a href="./matrix/matrix.py" target="_blank">Python (3.11.2)</a> | 0.552620 | 0.037042 | 2.28x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.74x faster than Helium
- Ruby (3.4.9) is 1.61x slower than Helium
- Perl (5.42.2) is 2.09x slower than Helium
- Python (3.11.2) is 2.28x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.140139 | 0.004660 | 3.45x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.408523 | 0.020999 | 1.18x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.483477 | 0.050917 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 0.879792 | 0.007878 | 1.82x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.087691 | 0.024262 | 2.25x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.45x faster than Helium
- Ruby (3.4.9) is 1.18x faster than Helium
- Python (3.11.2) is 1.82x slower than Helium
- Perl (5.42.2) is 2.25x slower than Helium

## sieve

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve/sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.107264 | 0.006557 | 1.90x faster |
| <a href="./sieve/sieve.he" target="_blank">Helium</a> | 0.204105 | 0.001312 | 1.00x (baseline) |
| <a href="./sieve/sieve.py" target="_blank">Python (3.11.2)</a> | 0.330755 | 0.013616 | 1.62x slower |
| <a href="./sieve/sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.344405 | 0.034278 | 1.69x slower |
| <a href="./sieve/sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.455184 | 0.003895 | 2.23x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.90x faster than Helium
- Python (3.11.2) is 1.62x slower than Helium
- Ruby (3.4.9) is 1.69x slower than Helium
- Perl (5.42.2) is 2.23x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.078915 | 0.002209 | 3.42x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.270002 | 0.005477 | 1.00x (baseline) |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.270010 | 0.014424 | 1.00x slower |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.462032 | 0.007442 | 1.71x slower |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.808452 | 0.080823 | 2.99x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.42x faster than Helium
- Ruby (3.4.9) is 1.00x slower than Helium
- Perl (5.42.2) is 1.71x slower than Helium
- Python (3.11.2) is 2.99x slower than Helium

## sqrt

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt/sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.083343 | 0.004885 | 1.44x faster |
| <a href="./sqrt/sqrt.he" target="_blank">Helium</a> | 0.120278 | 0.002628 | 1.00x (baseline) |
| <a href="./sqrt/sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.237928 | 0.002357 | 1.98x slower |
| <a href="./sqrt/sqrt.py" target="_blank">Python (3.11.2)</a> | 0.247809 | 0.016124 | 2.06x slower |
| <a href="./sqrt/sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.278896 | 0.005449 | 2.32x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.44x faster than Helium
- Perl (5.42.2) is 1.98x slower than Helium
- Python (3.11.2) is 2.06x slower than Helium
- Ruby (3.4.9) is 2.32x slower than Helium

## word-freq

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./word-freq/freq.he" target="_blank">Helium</a> | 0.776792 | 0.079934 | 1.00x (baseline) |
| <a href="./word-freq/freq.py" target="_blank">Python (3.11.2)</a> | 0.796781 | 0.010146 | 1.03x slower |
| <a href="./word-freq/freq.js" target="_blank">JavaScript (Node v26.3.0)</a> | 1.164688 | 0.048051 | 1.50x slower |
| <a href="./word-freq/freq.rb" target="_blank">Ruby (3.4.9)</a> | 1.261303 | 0.019990 | 1.62x slower |
| <a href="./word-freq/freq.pl" target="_blank">Perl (5.42.2)</a> | 1.556165 | 0.078716 | 2.00x slower |

### Helium comparison:
- Python (3.11.2) is 1.03x slower than Helium
- JavaScript (Node v26.3.0) is 1.50x slower than Helium
- Ruby (3.4.9) is 1.62x slower than Helium
- Perl (5.42.2) is 2.00x slower than Helium

