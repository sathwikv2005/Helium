# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.078915 | 0.002209 | 3.42x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.270002 | 0.005477 | 1.00x (baseline) |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.270010 | 0.014424 | 1.00x slower |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.462032 | 0.007442 | 1.71x slower |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.808452 | 0.080823 | 2.99x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.42x faster than Helium
- Ruby (3.4.9) is 1.00x slower than Helium
- Perl (5.42.2) is 1.71x slower than Helium
- Python (3.11.2) is 2.99x slower than Helium

