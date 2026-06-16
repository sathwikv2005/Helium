# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.101760 | 0.001619 | 3.45x faster |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.247434 | 0.003031 | 1.42x faster |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.281574 | 0.003508 | 1.25x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.351259 | 0.017053 | 1.00x (baseline) |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 0.962055 | 0.005029 | 2.74x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.45x faster than Helium
- Ruby (3.4.9) is 1.42x faster than Helium
- Python (3.11.2) is 1.25x faster than Helium
- Perl (5.42.2) is 2.74x slower than Helium

