# Benchmark Results (array-sum)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.094099 | 0.003951 | 1.26x faster |
| <a href="./sum.he" target="_blank">Helium</a> | 0.118204 | 0.001414 | 1.00x (baseline) |
| <a href="./sum.pl" target="_blank">Perl (5.42.2)</a> | 0.230723 | 0.002944 | 1.95x slower |
| <a href="./sum.py" target="_blank">Python (3.11.2)</a> | 0.234705 | 0.009825 | 1.99x slower |
| <a href="./sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.351405 | 0.023285 | 2.97x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.26x faster than Helium
- Perl (5.42.2) is 1.95x slower than Helium
- Python (3.11.2) is 1.99x slower than Helium
- Ruby (3.4.9) is 2.97x slower than Helium

