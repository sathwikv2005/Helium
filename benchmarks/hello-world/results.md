# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.026897 | 0.000703 | 1.00x (baseline) |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.051376 | 0.001180 | 1.91x slower |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.071575 | 0.001547 | 2.66x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.075764 | 0.002353 | 2.82x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.155375 | 0.003403 | 5.78x slower |

---

## Helium Comparison
- Perl (5.42.2) is 1.91x slower than Helium
- Python (3.11.2) is 2.66x slower than Helium
- JavaScript (Node v20.19.1) is 2.82x slower than Helium
- Ruby (3.4.9) is 5.78x slower than Helium

