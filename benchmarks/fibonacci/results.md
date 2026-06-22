# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.176422 | 0.004807 | 7.19x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.939940 | 0.022755 | 1.35x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.268299 | 0.008239 | 1.00x (baseline) |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.769670 | 0.023779 | 1.40x slower |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.190686 | 0.075949 | 4.88x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 7.19x faster than Helium
- Ruby (3.4.9) is 1.35x faster than Helium
- Python (3.11.2) is 1.40x slower than Helium
- Perl (5.42.2) is 4.88x slower than Helium

