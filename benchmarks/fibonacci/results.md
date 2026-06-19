# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.157319 | 0.003527 | 8.28x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.898011 | 0.010657 | 1.45x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.302273 | 0.012962 | 1.00x (baseline) |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.678081 | 0.018584 | 1.29x slower |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 5.985897 | 0.029493 | 4.60x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 8.28x faster than Helium
- Ruby (3.4.9) is 1.45x faster than Helium
- Python (3.11.2) is 1.29x slower than Helium
- Perl (5.42.2) is 4.60x slower than Helium

