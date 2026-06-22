# Benchmark Results (sqrt)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.094736 | 0.010317 | 1.52x faster |
| <a href="./sqrt.he" target="_blank">Helium</a> | 0.143621 | 0.006112 | 1.00x (baseline) |
| <a href="./sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.253164 | 0.009488 | 1.76x slower |
| <a href="./sqrt.py" target="_blank">Python (3.11.2)</a> | 0.273703 | 0.015776 | 1.91x slower |
| <a href="./sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.311471 | 0.008264 | 2.17x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.52x faster than Helium
- Perl (5.42.2) is 1.76x slower than Helium
- Python (3.11.2) is 1.91x slower than Helium
- Ruby (3.4.9) is 2.17x slower than Helium

