# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.023701 | 0.000515 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.046427 | 0.001282 | 1.96x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048908 | 0.001693 | 2.06x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.075221 | 0.005886 | 3.17x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.152342 | 0.009210 | 6.43x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.96x slower than Helium
- Perl (5.42.2) is 2.06x slower than Helium
- JavaScript (Node v26.3.0) is 3.17x slower than Helium
- Ruby (3.4.9) is 6.43x slower than Helium

