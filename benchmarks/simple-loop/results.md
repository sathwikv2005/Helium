# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.091446 | 0.004870 | 3.56x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.292545 | 0.010228 | 1.11x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.325143 | 0.010772 | 1.00x (baseline) |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.510699 | 0.022483 | 1.57x slower |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.890610 | 0.040873 | 2.74x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.56x faster than Helium
- Ruby (3.4.9) is 1.11x faster than Helium
- Perl (5.42.2) is 1.57x slower than Helium
- Python (3.11.2) is 2.74x slower than Helium

