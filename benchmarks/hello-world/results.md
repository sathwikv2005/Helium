# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.026902 | 0.002250 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.052469 | 0.002257 | 1.95x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.055096 | 0.001738 | 2.05x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.083497 | 0.003099 | 3.10x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.177595 | 0.013600 | 6.60x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.95x slower than Helium
- Perl (5.42.2) is 2.05x slower than Helium
- JavaScript (Node v26.3.0) is 3.10x slower than Helium
- Ruby (3.4.9) is 6.60x slower than Helium

