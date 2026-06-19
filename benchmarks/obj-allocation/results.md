# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.133196 | 0.002888 | 4.13x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.371498 | 0.018907 | 1.48x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.549644 | 0.036877 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 0.920045 | 0.050107 | 1.67x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.069691 | 0.025581 | 1.95x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 4.13x faster than Helium
- Ruby (3.4.9) is 1.48x faster than Helium
- Python (3.11.2) is 1.67x slower than Helium
- Perl (5.42.2) is 1.95x slower than Helium

