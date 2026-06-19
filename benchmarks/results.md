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
- Time: 2026-06-19 07:17:05

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 3.07x faster |
| Helium | 1.00x (baseline) |
| Ruby (3.4.9) | 1.17x slower |
| Python (3.11.2) | 1.50x slower |
| Perl (5.42.2) | 2.06x slower |

---

## array-sum

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./array-sum/sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.098517 | 0.006597 | 1.41x faster |
| <a href="./array-sum/sum.he" target="_blank">Helium</a> | 0.139141 | 0.007756 | 1.00x (baseline) |
| <a href="./array-sum/sum.py" target="_blank">Python (3.11.2)</a> | 0.228129 | 0.005604 | 1.64x slower |
| <a href="./array-sum/sum.pl" target="_blank">Perl (5.42.2)</a> | 0.229063 | 0.002257 | 1.65x slower |
| <a href="./array-sum/sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.340337 | 0.012854 | 2.45x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.41x faster than Helium
- Python (3.11.2) is 1.64x slower than Helium
- Perl (5.42.2) is 1.65x slower than Helium
- Ruby (3.4.9) is 2.45x slower than Helium

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099119 | 0.003689 | 2.77x faster |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.243012 | 0.005863 | 1.13x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.274237 | 0.009772 | 1.00x (baseline) |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.283514 | 0.004950 | 1.03x slower |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 0.996549 | 0.064001 | 3.63x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.77x faster than Helium
- Ruby (3.4.9) is 1.13x faster than Helium
- Python (3.11.2) is 1.03x slower than Helium
- Perl (5.42.2) is 3.63x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093272 | 0.004553 | 14.74x faster |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.875661 | 0.009761 | 1.57x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 1.375269 | 0.004775 | 1.00x (baseline) |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 1.935938 | 0.099507 | 1.41x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.105335 | 0.010669 | 1.53x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 14.74x faster than Helium
- Ruby (3.4.9) is 1.57x faster than Helium
- Python (3.11.2) is 1.41x slower than Helium
- Perl (5.42.2) is 1.53x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.157319 | 0.003527 | 8.28x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.898011 | 0.010657 | 1.45x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.302273 | 0.012962 | 1.00x (baseline) |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.678081 | 0.018584 | 1.29x slower |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 5.985897 | 0.029493 | 4.60x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 8.28x faster than Helium
- Ruby (3.4.9) is 1.45x faster than Helium
- Python (3.11.2) is 1.29x slower than Helium
- Perl (5.42.2) is 4.60x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.025167 | 0.000458 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.045769 | 0.002001 | 1.82x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048318 | 0.001246 | 1.92x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.071773 | 0.002187 | 2.85x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.150244 | 0.004334 | 5.97x slower |

### Helium comparison:
- Python (3.11.2) is 1.82x slower than Helium
- Perl (5.42.2) is 1.92x slower than Helium
- JavaScript (Node v26.3.0) is 2.85x slower than Helium
- Ruby (3.4.9) is 5.97x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.133196 | 0.002888 | 4.13x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.371498 | 0.018907 | 1.48x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.549644 | 0.036877 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 0.920045 | 0.050107 | 1.67x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.069691 | 0.025581 | 1.95x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 4.13x faster than Helium
- Ruby (3.4.9) is 1.48x faster than Helium
- Python (3.11.2) is 1.67x slower than Helium
- Perl (5.42.2) is 1.95x slower than Helium

## sieve

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve/sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.107789 | 0.016321 | 2.31x faster |
| <a href="./sieve/sieve.he" target="_blank">Helium</a> | 0.249035 | 0.004295 | 1.00x (baseline) |
| <a href="./sieve/sieve.py" target="_blank">Python (3.11.2)</a> | 0.324988 | 0.005367 | 1.30x slower |
| <a href="./sieve/sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.335447 | 0.007451 | 1.35x slower |
| <a href="./sieve/sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.450238 | 0.004657 | 1.81x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.31x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium
- Ruby (3.4.9) is 1.35x slower than Helium
- Perl (5.42.2) is 1.81x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.079384 | 0.008059 | 4.94x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.265640 | 0.009758 | 1.48x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.392220 | 0.007422 | 1.00x (baseline) |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.456041 | 0.022510 | 1.16x slower |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.830589 | 0.106110 | 2.12x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 4.94x faster than Helium
- Ruby (3.4.9) is 1.48x faster than Helium
- Perl (5.42.2) is 1.16x slower than Helium
- Python (3.11.2) is 2.12x slower than Helium

