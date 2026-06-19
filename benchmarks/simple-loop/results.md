# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.079384 | 0.008059 | 4.94x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.265640 | 0.009758 | 1.48x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.392220 | 0.007422 | 1.00x (baseline) |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.456041 | 0.022510 | 1.16x slower |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.830589 | 0.106110 | 2.12x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 4.94x faster than Helium
- Ruby (3.4.9) is 1.48x faster than Helium
- Perl (5.42.2) is 1.16x slower than Helium
- Python (3.11.2) is 2.12x slower than Helium

