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
- Time: 2026-06-23 01:03:19

---

## Overall Performance (Helium Baseline)

| Language | vs Helium |
|----------|-----------|
| JavaScript (Node v26.3.0) | 2.17x faster |
| Helium | 1.00x (baseline) |
| Ruby (3.4.9) | 1.51x slower |
| Python (3.11.2) | 1.71x slower |
| Perl (5.42.2) | 2.27x slower |

---

## array-sum

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./array-sum/sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.094303 | 0.003084 | 1.35x faster |
| <a href="./array-sum/sum.he" target="_blank">Helium</a> | 0.127691 | 0.001688 | 1.00x (baseline) |
| <a href="./array-sum/sum.pl" target="_blank">Perl (5.42.2)</a> | 0.235573 | 0.005429 | 1.84x slower |
| <a href="./array-sum/sum.py" target="_blank">Python (3.11.2)</a> | 0.238980 | 0.007218 | 1.87x slower |
| <a href="./array-sum/sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.379693 | 0.131756 | 2.97x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.35x faster than Helium
- Perl (5.42.2) is 1.84x slower than Helium
- Python (3.11.2) is 1.87x slower than Helium
- Ruby (3.4.9) is 2.97x slower than Helium

## b-tree

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./b-tree/tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.117470 | 0.012940 | 2.50x faster |
| <a href="./b-tree/tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.287968 | 0.012740 | 1.02x faster |
| <a href="./b-tree/tree.he" target="_blank">Helium</a> | 0.294066 | 0.006923 | 1.00x (baseline) |
| <a href="./b-tree/tree.py" target="_blank">Python (3.11.2)</a> | 0.335528 | 0.016613 | 1.14x slower |
| <a href="./b-tree/tree.pl" target="_blank">Perl (5.42.2)</a> | 1.061351 | 0.036032 | 3.61x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.50x faster than Helium
- Ruby (3.4.9) is 1.02x faster than Helium
- Python (3.11.2) is 1.14x slower than Helium
- Perl (5.42.2) is 3.61x slower than Helium

## compute-pi

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./compute-pi/pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.102365 | 0.005465 | 7.73x faster |
| <a href="./compute-pi/pi.he" target="_blank">Helium</a> | 0.791643 | 0.013303 | 1.00x (baseline) |
| <a href="./compute-pi/pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.935723 | 0.168135 | 1.18x slower |
| <a href="./compute-pi/pi.py" target="_blank">Python (3.11.2)</a> | 2.009823 | 0.121537 | 2.54x slower |
| <a href="./compute-pi/pi.pl" target="_blank">Perl (5.42.2)</a> | 2.144395 | 0.013082 | 2.71x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 7.73x faster than Helium
- Ruby (3.4.9) is 1.18x slower than Helium
- Python (3.11.2) is 2.54x slower than Helium
- Perl (5.42.2) is 2.71x slower than Helium

## fibonacci

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fibonacci/fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.176422 | 0.004807 | 7.19x faster |
| <a href="./fibonacci/fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.939940 | 0.022755 | 1.35x faster |
| <a href="./fibonacci/fib.he" target="_blank">Helium</a> | 1.268299 | 0.008239 | 1.00x (baseline) |
| <a href="./fibonacci/fib.py" target="_blank">Python (3.11.2)</a> | 1.769670 | 0.023779 | 1.40x slower |
| <a href="./fibonacci/fib.pl" target="_blank">Perl (5.42.2)</a> | 6.190686 | 0.075949 | 4.88x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 7.19x faster than Helium
- Ruby (3.4.9) is 1.35x faster than Helium
- Python (3.11.2) is 1.40x slower than Helium
- Perl (5.42.2) is 4.88x slower than Helium

## hello-world

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello-world/hello.he" target="_blank">Helium</a> | 0.026902 | 0.002250 | 1.00x (baseline) |
| <a href="./hello-world/hello.py" target="_blank">Python (3.11.2)</a> | 0.052469 | 0.002257 | 1.95x slower |
| <a href="./hello-world/hello.pl" target="_blank">Perl (5.42.2)</a> | 0.055096 | 0.001738 | 2.05x slower |
| <a href="./hello-world/hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.083497 | 0.003099 | 3.10x slower |
| <a href="./hello-world/hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.177595 | 0.013600 | 6.60x slower |

### Helium comparison:
- Python (3.11.2) is 1.95x slower than Helium
- Perl (5.42.2) is 2.05x slower than Helium
- JavaScript (Node v26.3.0) is 3.10x slower than Helium
- Ruby (3.4.9) is 6.60x slower than Helium

## matrix

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./matrix/matrix.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.100438 | 0.005860 | 2.93x faster |
| <a href="./matrix/matrix.he" target="_blank">Helium</a> | 0.294210 | 0.007394 | 1.00x (baseline) |
| <a href="./matrix/matrix.rb" target="_blank">Ruby (3.4.9)</a> | 0.441424 | 0.019236 | 1.50x slower |
| <a href="./matrix/matrix.py" target="_blank">Python (3.11.2)</a> | 0.543690 | 0.039630 | 1.85x slower |
| <a href="./matrix/matrix.pl" target="_blank">Perl (5.42.2)</a> | 0.595757 | 0.016933 | 2.02x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 2.93x faster than Helium
- Ruby (3.4.9) is 1.50x slower than Helium
- Python (3.11.2) is 1.85x slower than Helium
- Perl (5.42.2) is 2.02x slower than Helium

## obj-allocation

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./obj-allocation/allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.152586 | 0.009701 | 3.72x faster |
| <a href="./obj-allocation/allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.416400 | 0.021593 | 1.36x faster |
| <a href="./obj-allocation/allocate.he" target="_blank">Helium</a> | 0.567638 | 0.007255 | 1.00x (baseline) |
| <a href="./obj-allocation/allocate.py" target="_blank">Python (3.11.2)</a> | 1.013885 | 0.045182 | 1.79x slower |
| <a href="./obj-allocation/allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.172749 | 0.026821 | 2.07x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.72x faster than Helium
- Ruby (3.4.9) is 1.36x faster than Helium
- Python (3.11.2) is 1.79x slower than Helium
- Perl (5.42.2) is 2.07x slower than Helium

## sieve

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve/sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.122890 | 0.005217 | 1.89x faster |
| <a href="./sieve/sieve.he" target="_blank">Helium</a> | 0.232848 | 0.006104 | 1.00x (baseline) |
| <a href="./sieve/sieve.py" target="_blank">Python (3.11.2)</a> | 0.361056 | 0.020779 | 1.55x slower |
| <a href="./sieve/sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.396278 | 0.020330 | 1.70x slower |
| <a href="./sieve/sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.494505 | 0.007606 | 2.12x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.89x faster than Helium
- Python (3.11.2) is 1.55x slower than Helium
- Ruby (3.4.9) is 1.70x slower than Helium
- Perl (5.42.2) is 2.12x slower than Helium

## simple-loop

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./simple-loop/loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.091446 | 0.004870 | 3.56x faster |
| <a href="./simple-loop/loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.292545 | 0.010228 | 1.11x faster |
| <a href="./simple-loop/loop.he" target="_blank">Helium</a> | 0.325143 | 0.010772 | 1.00x (baseline) |
| <a href="./simple-loop/loop.pl" target="_blank">Perl (5.42.2)</a> | 0.510699 | 0.022483 | 1.57x slower |
| <a href="./simple-loop/loop.py" target="_blank">Python (3.11.2)</a> | 0.890610 | 0.040873 | 2.74x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 3.56x faster than Helium
- Ruby (3.4.9) is 1.11x faster than Helium
- Perl (5.42.2) is 1.57x slower than Helium
- Python (3.11.2) is 2.74x slower than Helium

## sqrt

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt/sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.094736 | 0.010317 | 1.52x faster |
| <a href="./sqrt/sqrt.he" target="_blank">Helium</a> | 0.143621 | 0.006112 | 1.00x (baseline) |
| <a href="./sqrt/sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.253164 | 0.009488 | 1.76x slower |
| <a href="./sqrt/sqrt.py" target="_blank">Python (3.11.2)</a> | 0.273703 | 0.015776 | 1.91x slower |
| <a href="./sqrt/sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.311471 | 0.008264 | 2.17x slower |

### Helium comparison:
- JavaScript (Node v26.3.0) is 1.52x faster than Helium
- Perl (5.42.2) is 1.76x slower than Helium
- Python (3.11.2) is 1.91x slower than Helium
- Ruby (3.4.9) is 2.17x slower than Helium

## word-freq

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./word-freq/freq.py" target="_blank">Python (3.11.2)</a> | 0.925295 | 0.081383 | 1.06x faster |
| <a href="./word-freq/freq.he" target="_blank">Helium</a> | 0.979589 | 0.026484 | 1.00x (baseline) |
| <a href="./word-freq/freq.js" target="_blank">JavaScript (Node v26.3.0)</a> | 1.316953 | 0.068527 | 1.34x slower |
| <a href="./word-freq/freq.rb" target="_blank">Ruby (3.4.9)</a> | 1.439344 | 0.041587 | 1.47x slower |
| <a href="./word-freq/freq.pl" target="_blank">Perl (5.42.2)</a> | 1.802743 | 0.043219 | 1.84x slower |

### Helium comparison:
- Python (3.11.2) is 1.06x faster than Helium
- JavaScript (Node v26.3.0) is 1.34x slower than Helium
- Ruby (3.4.9) is 1.47x slower than Helium
- Perl (5.42.2) is 1.84x slower than Helium

