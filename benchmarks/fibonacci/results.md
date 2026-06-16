# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.160238 | 0.002743 | 10.38x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.901254 | 0.009337 | 1.84x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.662731 | 0.008129 | 1.00x (baseline) |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.670612 | 0.021518 | 1.00x slower |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.013688 | 0.031328 | 3.62x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 10.38x faster than Helium
- Ruby (3.4.9) is 1.84x faster than Helium
- Python (3.11.2) is 1.00x slower than Helium
- Perl (5.42.2) is 3.62x slower than Helium

