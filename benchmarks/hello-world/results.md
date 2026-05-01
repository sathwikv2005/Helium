# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.022585 | 0.001144 | 1.00x (baseline) |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.046196 | 0.001582 | 2.05x slower |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.061529 | 0.002772 | 2.72x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.070485 | 0.001919 | 3.12x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.162125 | 0.008262 | 7.18x slower |

---

## Helium Comparison
- Perl (5.42.2) is 2.05x slower than Helium
- Python (3.11.2) is 2.72x slower than Helium
- JavaScript (Node v20.19.1) is 3.12x slower than Helium
- Ruby (3.4.9) is 7.18x slower than Helium

