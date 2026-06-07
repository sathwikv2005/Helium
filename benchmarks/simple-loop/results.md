# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.091222 | 0.002620 | 7.58x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.295268 | 0.010984 | 2.34x faster |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.530766 | 0.030268 | 1.30x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.691641 | 0.022458 | 1.00x (baseline) |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.900588 | 0.074519 | 1.30x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 7.58x faster than Helium
- Ruby (3.4.9) is 2.34x faster than Helium
- Perl (5.42.2) is 1.30x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium

