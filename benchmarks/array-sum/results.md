# Benchmark Results (array-sum)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.102668 | 0.019067 | 1.23x faster |
| <a href="./sum.he" target="_blank">Helium</a> | 0.126168 | 0.004822 | 1.00x (baseline) |
| <a href="./sum.py" target="_blank">Python (3.11.2)</a> | 0.230242 | 0.002938 | 1.82x slower |
| <a href="./sum.pl" target="_blank">Perl (5.42.2)</a> | 0.233406 | 0.016550 | 1.85x slower |
| <a href="./sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.353018 | 0.020128 | 2.80x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.23x faster than Helium
- Python (3.11.2) is 1.82x slower than Helium
- Perl (5.42.2) is 1.85x slower than Helium
- Ruby (3.4.9) is 2.80x slower than Helium

