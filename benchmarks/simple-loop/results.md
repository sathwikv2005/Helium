# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.076664 | 0.001415 | 4.14x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.266333 | 0.012063 | 1.19x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.317681 | 0.009001 | 1.00x (baseline) |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.473549 | 0.072667 | 1.49x slower |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.854499 | 0.065642 | 2.69x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 4.14x faster than Helium
- Ruby (3.4.9) is 1.19x faster than Helium
- Perl (5.42.2) is 1.49x slower than Helium
- Python (3.11.2) is 2.69x slower than Helium

