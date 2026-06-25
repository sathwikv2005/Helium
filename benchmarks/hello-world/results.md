# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.022857 | 0.000555 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.12.11)</a> | 0.049840 | 0.001433 | 2.18x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.051514 | 0.003976 | 2.25x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.076782 | 0.006444 | 3.36x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.149598 | 0.005943 | 6.55x slower |

---

## Helium Comparison
- Python (3.12.11) is 2.18x slower than Helium
- Perl (5.42.2) is 2.25x slower than Helium
- JavaScript (Node v26.3.0) is 3.36x slower than Helium
- Ruby (3.4.9) is 6.55x slower than Helium

