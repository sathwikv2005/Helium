# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.092281 | 0.001142 | 18.25x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.914591 | 0.015502 | 1.84x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 1.683933 | 0.011744 | 1.00x (baseline) |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.993279 | 0.068628 | 1.18x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.130412 | 0.011854 | 1.27x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 18.25x faster than Helium
- Ruby (3.4.9) is 1.84x faster than Helium
- Python (3.11.2) is 1.18x slower than Helium
- Perl (5.42.2) is 1.27x slower than Helium

