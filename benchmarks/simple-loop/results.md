# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.081967 | 0.001421 | 7.99x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.260488 | 0.003212 | 2.51x faster |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.473465 | 0.007886 | 1.38x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.654819 | 0.009894 | 1.00x (baseline) |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.848664 | 0.035658 | 1.30x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 7.99x faster than Helium
- Ruby (3.4.9) is 2.51x faster than Helium
- Perl (5.42.2) is 1.38x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium

