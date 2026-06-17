# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.131199 | 0.001119 | 4.05x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.367660 | 0.032096 | 1.44x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.531004 | 0.007639 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 0.890718 | 0.046080 | 1.68x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.095245 | 0.050254 | 2.06x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 4.05x faster than Helium
- Ruby (3.4.9) is 1.44x faster than Helium
- Python (3.11.2) is 1.68x slower than Helium
- Perl (5.42.2) is 2.06x slower than Helium

