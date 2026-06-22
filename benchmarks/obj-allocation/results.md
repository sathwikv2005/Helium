# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.152586 | 0.009701 | 3.72x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.416400 | 0.021593 | 1.36x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.567638 | 0.007255 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 1.013885 | 0.045182 | 1.79x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.172749 | 0.026821 | 2.07x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.72x faster than Helium
- Ruby (3.4.9) is 1.36x faster than Helium
- Python (3.11.2) is 1.79x slower than Helium
- Perl (5.42.2) is 2.07x slower than Helium

