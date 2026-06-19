# Benchmark Results (array-sum)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.098517 | 0.006597 | 1.41x faster |
| <a href="./sum.he" target="_blank">Helium</a> | 0.139141 | 0.007756 | 1.00x (baseline) |
| <a href="./sum.py" target="_blank">Python (3.11.2)</a> | 0.228129 | 0.005604 | 1.64x slower |
| <a href="./sum.pl" target="_blank">Perl (5.42.2)</a> | 0.229063 | 0.002257 | 1.65x slower |
| <a href="./sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.340337 | 0.012854 | 2.45x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.41x faster than Helium
- Python (3.11.2) is 1.64x slower than Helium
- Perl (5.42.2) is 1.65x slower than Helium
- Ruby (3.4.9) is 2.45x slower than Helium

