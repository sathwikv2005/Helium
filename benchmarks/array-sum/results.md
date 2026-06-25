# Benchmark Results (array-sum)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093878 | 0.006360 | 1.50x faster |
| <a href="./sum.he" target="_blank">Helium</a> | 0.141040 | 0.005238 | 1.00x (baseline) |
| <a href="./sum.pl" target="_blank">Perl (5.42.2)</a> | 0.248553 | 0.007417 | 1.76x slower |
| <a href="./sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.353240 | 0.008835 | 2.50x slower |
| <a href="./sum.py" target="_blank">Python (3.12.11)</a> | 0.394820 | 0.014132 | 2.80x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.50x faster than Helium
- Perl (5.42.2) is 1.76x slower than Helium
- Ruby (3.4.9) is 2.50x slower than Helium
- Python (3.12.11) is 2.80x slower than Helium

