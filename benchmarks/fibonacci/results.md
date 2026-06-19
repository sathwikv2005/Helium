# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.160001 | 0.003662 | 7.65x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.882000 | 0.006867 | 1.39x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.223986 | 0.020903 | 1.00x (baseline) |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.680429 | 0.038997 | 1.37x slower |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.009357 | 0.068025 | 4.91x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 7.65x faster than Helium
- Ruby (3.4.9) is 1.39x faster than Helium
- Python (3.11.2) is 1.37x slower than Helium
- Perl (5.42.2) is 4.91x slower than Helium

