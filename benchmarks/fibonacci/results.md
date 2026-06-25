# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.161885 | 0.004260 | 7.79x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.900740 | 0.018643 | 1.40x faster |
| <a href="./fib.py" target="_blank">Python (3.12.11)</a> | 1.200102 | 0.021507 | 1.05x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.260681 | 0.035789 | 1.00x (baseline) |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 5.986817 | 0.044561 | 4.75x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 7.79x faster than Helium
- Ruby (3.4.9) is 1.40x faster than Helium
- Python (3.12.11) is 1.05x faster than Helium
- Perl (5.42.2) is 4.75x slower than Helium

