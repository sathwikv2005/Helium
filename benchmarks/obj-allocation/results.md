# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.131283 | 0.002273 | 3.71x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.366083 | 0.003378 | 1.33x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.486459 | 0.010556 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 0.789445 | 0.009081 | 1.62x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.077899 | 0.012821 | 2.22x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.71x faster than Helium
- Ruby (3.4.9) is 1.33x faster than Helium
- Python (3.11.2) is 1.62x slower than Helium
- Perl (5.42.2) is 2.22x slower than Helium

