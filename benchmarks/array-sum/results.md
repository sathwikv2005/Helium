# Benchmark Results (array-sum)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093856 | 0.003199 | 1.27x faster |
| <a href="./sum.he" target="_blank">Helium</a> | 0.119363 | 0.003032 | 1.00x (baseline) |
| <a href="./sum.py" target="_blank">Python (3.11.2)</a> | 0.225939 | 0.005704 | 1.89x slower |
| <a href="./sum.pl" target="_blank">Perl (5.42.2)</a> | 0.228935 | 0.001389 | 1.92x slower |
| <a href="./sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.348458 | 0.013377 | 2.92x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.27x faster than Helium
- Python (3.11.2) is 1.89x slower than Helium
- Perl (5.42.2) is 1.92x slower than Helium
- Ruby (3.4.9) is 2.92x slower than Helium

