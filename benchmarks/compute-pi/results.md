# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099078 | 0.003300 | 9.58x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.923893 | 0.018067 | 1.03x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 0.949483 | 0.011640 | 1.00x (baseline) |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.357390 | 0.033631 | 2.48x slower |
| <a href="./pi.py" target="_blank">Python (3.12.11)</a> | 3.604538 | 0.076443 | 3.80x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 9.58x faster than Helium
- Ruby (3.4.9) is 1.03x faster than Helium
- Perl (5.42.2) is 2.48x slower than Helium
- Python (3.12.11) is 3.80x slower than Helium

