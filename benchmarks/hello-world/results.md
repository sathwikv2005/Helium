# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.025167 | 0.000458 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.045769 | 0.002001 | 1.82x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048318 | 0.001246 | 1.92x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.071773 | 0.002187 | 2.85x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.150244 | 0.004334 | 5.97x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.82x slower than Helium
- Perl (5.42.2) is 1.92x slower than Helium
- JavaScript (Node v26.3.0) is 2.85x slower than Helium
- Ruby (3.4.9) is 5.97x slower than Helium

