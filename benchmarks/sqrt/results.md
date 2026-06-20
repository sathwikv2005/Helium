# Benchmark Results (sqrt)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.081071 | 0.001385 | 1.54x faster |
| <a href="./sqrt.he" target="_blank">Helium</a> | 0.124693 | 0.001680 | 1.00x (baseline) |
| <a href="./sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.249222 | 0.017076 | 2.00x slower |
| <a href="./sqrt.py" target="_blank">Python (3.11.2)</a> | 0.265520 | 0.020368 | 2.13x slower |
| <a href="./sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.278430 | 0.005766 | 2.23x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.54x faster than Helium
- Perl (5.42.2) is 2.00x slower than Helium
- Python (3.11.2) is 2.13x slower than Helium
- Ruby (3.4.9) is 2.23x slower than Helium

