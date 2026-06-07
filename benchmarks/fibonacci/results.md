# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.224093 | 0.050374 | 8.22x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.993709 | 0.032538 | 1.85x faster |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.784319 | 0.032100 | 1.03x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.841464 | 0.040315 | 1.00x (baseline) |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.429229 | 0.108411 | 3.49x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 8.22x faster than Helium
- Ruby (3.4.9) is 1.85x faster than Helium
- Python (3.11.2) is 1.03x faster than Helium
- Perl (5.42.2) is 3.49x slower than Helium

