# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.080376 | 0.001401 | 5.02x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.254288 | 0.011920 | 1.59x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.403764 | 0.003103 | 1.00x (baseline) |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.454579 | 0.009699 | 1.13x slower |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.893593 | 0.066504 | 2.21x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 5.02x faster than Helium
- Ruby (3.4.9) is 1.59x faster than Helium
- Perl (5.42.2) is 1.13x slower than Helium
- Python (3.11.2) is 2.21x slower than Helium

