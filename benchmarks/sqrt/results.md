# Benchmark Results (sqrt)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.083343 | 0.004885 | 1.44x faster |
| <a href="./sqrt.he" target="_blank">Helium</a> | 0.120278 | 0.002628 | 1.00x (baseline) |
| <a href="./sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.237928 | 0.002357 | 1.98x slower |
| <a href="./sqrt.py" target="_blank">Python (3.11.2)</a> | 0.247809 | 0.016124 | 2.06x slower |
| <a href="./sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.278896 | 0.005449 | 2.32x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.44x faster than Helium
- Perl (5.42.2) is 1.98x slower than Helium
- Python (3.11.2) is 2.06x slower than Helium
- Ruby (3.4.9) is 2.32x slower than Helium

