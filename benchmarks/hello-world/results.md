# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.029124 | 0.000591 | 1.00x (baseline) |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.058312 | 0.005352 | 2.00x slower |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.081809 | 0.002340 | 2.81x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.089214 | 0.007789 | 3.06x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.181719 | 0.007023 | 6.24x slower |

---

## Helium Comparison
- Perl (5.42.2) is 2.00x slower than Helium
- Python (3.11.2) is 2.81x slower than Helium
- JavaScript (Node v20.19.1) is 3.06x slower than Helium
- Ruby (3.4.9) is 6.24x slower than Helium

