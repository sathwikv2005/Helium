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
- Time: 2026-06-21 00:53:09

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 2.48x faster |
| Helium | 1.00x (baseline) |
| Ruby (3.4.9) | 1.51x slower |
| Python (3.11.2) | 1.89x slower |
| Perl (5.42.2) | 2.37x slower |

---

## array-sum

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./array-sum/sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.094099 | 0.003951 | 1.26x faster |
| <a href="./array-sum/sum.he" target="_blank">Helium</a> | 0.118204 | 0.001414 | 1.00x (baseline) |
| <a href="./array-sum/sum.pl" target="_blank">Perl (5.42.2)</a> | 0.230723 | 0.002944 | 1.95x slower |
| <a href="./array-sum/sum.py" target="_blank">Python (3.11.2)</a> | 0.234705 | 0.009825 | 1.99x slower |
| <a href="./array-sum/sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.351405 | 0.023285 | 2.97x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.26x faster than Helium
- Perl (5.42.2) is 1.95x slower than Helium
- Python (3.11.2) is 1.99x slower than Helium
- Ruby (3.4.9) is 2.97x slower than Helium

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.103651 | 0.007204 | 2.47x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.255600 | 0.016231 | 1.00x (baseline) |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.292778 | 0.039269 | 1.15x slower |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.328565 | 0.062163 | 1.29x slower |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 0.980609 | 0.036896 | 3.84x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.47x faster than Helium
- Ruby (3.4.9) is 1.15x slower than Helium
- Python (3.11.2) is 1.29x slower than Helium
- Perl (5.42.2) is 3.84x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.091829 | 0.014356 | 8.81x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 0.809144 | 0.045852 | 1.00x (baseline) |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.929120 | 0.044664 | 1.15x slower |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.992682 | 0.067104 | 2.46x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.167597 | 0.035095 | 2.68x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 8.81x faster than Helium
- Ruby (3.4.9) is 1.15x slower than Helium
- Python (3.11.2) is 2.46x slower than Helium
- Perl (5.42.2) is 2.68x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.168662 | 0.005502 | 7.53x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.917842 | 0.022272 | 1.38x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.270517 | 0.038031 | 1.00x (baseline) |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.784834 | 0.058916 | 1.40x slower |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.200370 | 0.065095 | 4.88x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 7.53x faster than Helium
- Ruby (3.4.9) is 1.38x faster than Helium
- Python (3.11.2) is 1.40x slower than Helium
- Perl (5.42.2) is 4.88x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.023701 | 0.000515 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.046427 | 0.001282 | 1.96x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048908 | 0.001693 | 2.06x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.075221 | 0.005886 | 3.17x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.152342 | 0.009210 | 6.43x slower |

### Helium comparison:
- Python (3.11.2) is 1.96x slower than Helium
- Perl (5.42.2) is 2.06x slower than Helium
- JavaScript (Node v26.3.0) is 3.17x slower than Helium
- Ruby (3.4.9) is 6.43x slower than Helium

## matrix

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./matrix/matrix.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.094123 | 0.002499 | 2.85x faster |
| <a href="./matrix/matrix.he" target="_blank">Helium</a> | 0.267922 | 0.008483 | 1.00x (baseline) |
| <a href="./matrix/matrix.rb" target="_blank">Ruby (3.4.9)</a> | 0.390658 | 0.012577 | 1.46x slower |
| <a href="./matrix/matrix.pl" target="_blank">Perl (5.42.2)</a> | 0.496471 | 0.096142 | 1.85x slower |
| <a href="./matrix/matrix.py" target="_blank">Python (3.11.2)</a> | 0.529097 | 0.025322 | 1.97x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.85x faster than Helium
- Ruby (3.4.9) is 1.46x slower than Helium
- Perl (5.42.2) is 1.85x slower than Helium
- Python (3.11.2) is 1.97x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.137779 | 0.005135 | 3.54x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.368314 | 0.006775 | 1.32x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.487196 | 0.009346 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 0.912282 | 0.035168 | 1.87x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.107704 | 0.010991 | 2.27x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.54x faster than Helium
- Ruby (3.4.9) is 1.32x faster than Helium
- Python (3.11.2) is 1.87x slower than Helium
- Perl (5.42.2) is 2.27x slower than Helium

## sieve

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve/sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.102601 | 0.002171 | 2.10x faster |
| <a href="./sieve/sieve.he" target="_blank">Helium</a> | 0.215114 | 0.006416 | 1.00x (baseline) |
| <a href="./sieve/sieve.py" target="_blank">Python (3.11.2)</a> | 0.342832 | 0.017552 | 1.59x slower |
| <a href="./sieve/sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.348108 | 0.039668 | 1.62x slower |
| <a href="./sieve/sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.467573 | 0.020075 | 2.17x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.10x faster than Helium
- Python (3.11.2) is 1.59x slower than Helium
- Ruby (3.4.9) is 1.62x slower than Helium
- Perl (5.42.2) is 2.17x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.076664 | 0.001415 | 4.14x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.266333 | 0.012063 | 1.19x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.317681 | 0.009001 | 1.00x (baseline) |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.473549 | 0.072667 | 1.49x slower |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.854499 | 0.065642 | 2.69x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 4.14x faster than Helium
- Ruby (3.4.9) is 1.19x faster than Helium
- Perl (5.42.2) is 1.49x slower than Helium
- Python (3.11.2) is 2.69x slower than Helium

## sqrt

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt/sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.081071 | 0.001385 | 1.54x faster |
| <a href="./sqrt/sqrt.he" target="_blank">Helium</a> | 0.124693 | 0.001680 | 1.00x (baseline) |
| <a href="./sqrt/sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.249222 | 0.017076 | 2.00x slower |
| <a href="./sqrt/sqrt.py" target="_blank">Python (3.11.2)</a> | 0.265520 | 0.020368 | 2.13x slower |
| <a href="./sqrt/sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.278430 | 0.005766 | 2.23x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.54x faster than Helium
- Perl (5.42.2) is 2.00x slower than Helium
- Python (3.11.2) is 2.13x slower than Helium
- Ruby (3.4.9) is 2.23x slower than Helium

