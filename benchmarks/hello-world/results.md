# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.023907 | 0.000922 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.045760 | 0.001360 | 1.91x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048740 | 0.001040 | 2.04x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.073864 | 0.002057 | 3.09x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.146524 | 0.001451 | 6.13x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.91x slower than Helium
- Perl (5.42.2) is 2.04x slower than Helium
- JavaScript (Node v26.3.0) is 3.09x slower than Helium
- Ruby (3.4.9) is 6.13x slower than Helium

