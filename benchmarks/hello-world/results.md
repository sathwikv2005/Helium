# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.027171 | 0.001373 | 1.00x (baseline) |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.051632 | 0.001344 | 1.90x slower |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.068279 | 0.001507 | 2.51x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.075134 | 0.002653 | 2.77x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.156342 | 0.009846 | 5.75x slower |

---

## Helium Comparison
- Perl (5.42.2) is 1.90x slower than Helium
- Python (3.11.2) is 2.51x slower than Helium
- JavaScript (Node v20.19.1) is 2.77x slower than Helium
- Ruby (3.4.9) is 5.75x slower than Helium

