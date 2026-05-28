# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.082743 | 0.002938 | 7.86x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.256615 | 0.013367 | 2.53x faster |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.469550 | 0.018882 | 1.38x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.649956 | 0.021148 | 1.00x (baseline) |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.801460 | 0.022633 | 1.23x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 7.86x faster than Helium
- Ruby (3.4.9) is 2.53x faster than Helium
- Perl (5.42.2) is 1.38x faster than Helium
- Python (3.11.2) is 1.23x slower than Helium

