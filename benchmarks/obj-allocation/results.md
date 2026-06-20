# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.137779 | 0.005135 | 3.54x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.368314 | 0.006775 | 1.32x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.487196 | 0.009346 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 0.912282 | 0.035168 | 1.87x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.107704 | 0.010991 | 2.27x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.54x faster than Helium
- Ruby (3.4.9) is 1.32x faster than Helium
- Python (3.11.2) is 1.87x slower than Helium
- Perl (5.42.2) is 2.27x slower than Helium

