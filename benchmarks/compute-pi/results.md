# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093272 | 0.004553 | 14.74x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.875661 | 0.009761 | 1.57x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 1.375269 | 0.004775 | 1.00x (baseline) |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.935938 | 0.099507 | 1.41x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.105335 | 0.010669 | 1.53x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 14.74x faster than Helium
- Ruby (3.4.9) is 1.57x faster than Helium
- Python (3.11.2) is 1.41x slower than Helium
- Perl (5.42.2) is 1.53x slower than Helium

