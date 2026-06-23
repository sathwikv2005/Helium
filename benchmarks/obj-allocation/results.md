# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.140139 | 0.004660 | 3.45x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.408523 | 0.020999 | 1.18x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.483477 | 0.050917 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 0.879792 | 0.007878 | 1.82x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.087691 | 0.024262 | 2.25x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.45x faster than Helium
- Ruby (3.4.9) is 1.18x faster than Helium
- Python (3.11.2) is 1.82x slower than Helium
- Perl (5.42.2) is 2.25x slower than Helium

