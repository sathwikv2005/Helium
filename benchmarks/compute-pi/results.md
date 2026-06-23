# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.088462 | 0.001306 | 7.66x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 0.677322 | 0.016002 | 1.00x (baseline) |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.884048 | 0.008440 | 1.31x slower |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.912902 | 0.059005 | 2.82x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.104410 | 0.014818 | 3.11x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 7.66x faster than Helium
- Ruby (3.4.9) is 1.31x slower than Helium
- Python (3.11.2) is 2.82x slower than Helium
- Perl (5.42.2) is 3.11x slower than Helium

