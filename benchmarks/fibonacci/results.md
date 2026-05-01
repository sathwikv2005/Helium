# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.158774 | 0.001992 | 11.28x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.893956 | 0.016700 | 2.00x faster |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.661509 | 0.021084 | 1.08x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.790530 | 0.009120 | 1.00x (baseline) |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.070506 | 0.044750 | 3.39x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 11.28x faster than Helium
- Ruby (3.4.9) is 2.00x faster than Helium
- Python (3.11.2) is 1.08x faster than Helium
- Perl (5.42.2) is 3.39x slower than Helium

