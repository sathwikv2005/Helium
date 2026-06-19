# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.086739 | 0.005343 | 8.54x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 0.740944 | 0.015742 | 1.00x (baseline) |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.879630 | 0.010708 | 1.19x slower |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.943347 | 0.090564 | 2.62x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.103575 | 0.026837 | 2.84x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 8.54x faster than Helium
- Ruby (3.4.9) is 1.19x slower than Helium
- Python (3.11.2) is 2.62x slower than Helium
- Perl (5.42.2) is 2.84x slower than Helium

