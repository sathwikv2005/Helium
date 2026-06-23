# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.162350 | 0.011141 | 7.17x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.902243 | 0.044107 | 1.29x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.163597 | 0.012462 | 1.00x (baseline) |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.680821 | 0.019684 | 1.44x slower |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 5.973498 | 0.028061 | 5.13x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 7.17x faster than Helium
- Ruby (3.4.9) is 1.29x faster than Helium
- Python (3.11.2) is 1.44x slower than Helium
- Perl (5.42.2) is 5.13x slower than Helium

