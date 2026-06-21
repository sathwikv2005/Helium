# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.168662 | 0.005502 | 7.53x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.917842 | 0.022272 | 1.38x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.270517 | 0.038031 | 1.00x (baseline) |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.784834 | 0.058916 | 1.40x slower |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.200370 | 0.065095 | 4.88x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 7.53x faster than Helium
- Ruby (3.4.9) is 1.38x faster than Helium
- Python (3.11.2) is 1.40x slower than Helium
- Perl (5.42.2) is 4.88x slower than Helium

