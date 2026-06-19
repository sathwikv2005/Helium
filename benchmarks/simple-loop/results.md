# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.078433 | 0.001173 | 3.67x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.251994 | 0.020598 | 1.14x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.288108 | 0.010043 | 1.00x (baseline) |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.459264 | 0.013767 | 1.59x slower |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.835090 | 0.056183 | 2.90x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.67x faster than Helium
- Ruby (3.4.9) is 1.14x faster than Helium
- Perl (5.42.2) is 1.59x slower than Helium
- Python (3.11.2) is 2.90x slower than Helium

