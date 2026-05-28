# Benchmark Results (fibonacci)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./fib.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.159329 | 0.007614 | 10.92x faster |
| <a href="./fib.rb" target="_blank">Ruby (3.4.9)</a> | 0.885015 | 0.005847 | 1.97x faster |
| <a href="./fib.py" target="_blank">Python (3.11.2)</a> | 1.677910 | 0.015736 | 1.04x faster |
| <a href="./fib.he" target="_blank">Helium</a> | 1.740047 | 0.007794 | 1.00x (baseline) |
| <a href="./fib.pl" target="_blank">Perl (5.42.2)</a> | 6.045096 | 0.050558 | 3.47x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 10.92x faster than Helium
- Ruby (3.4.9) is 1.97x faster than Helium
- Python (3.11.2) is 1.04x faster than Helium
- Perl (5.42.2) is 3.47x slower than Helium

