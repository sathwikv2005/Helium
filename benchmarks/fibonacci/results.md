# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.158203 | 0.001535 | 8.35x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.897036 | 0.022816 | 1.47x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.321453 | 0.006457 | 1.00x (baseline) |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.663919 | 0.009830 | 1.26x slower |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 5.991210 | 0.035825 | 4.53x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 8.35x faster than Helium
- Ruby (3.4.9) is 1.47x faster than Helium
- Python (3.11.2) is 1.26x slower than Helium
- Perl (5.42.2) is 4.53x slower than Helium

