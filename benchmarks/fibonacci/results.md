# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.175656 | 0.005066 | 10.24x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.900480 | 0.022006 | 2.00x faster |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.691176 | 0.026745 | 1.06x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.798218 | 0.032030 | 1.00x (baseline) |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.108901 | 0.072070 | 3.40x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 10.24x faster than Helium
- Ruby (3.4.9) is 2.00x faster than Helium
- Python (3.11.2) is 1.06x faster than Helium
- Perl (5.42.2) is 3.40x slower than Helium

