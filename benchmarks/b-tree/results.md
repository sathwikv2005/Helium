# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.096452 | 0.002140 | 2.72x faster |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.247743 | 0.002857 | 1.06x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.262059 | 0.002928 | 1.00x (baseline) |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.280476 | 0.003310 | 1.07x slower |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 0.969861 | 0.026877 | 3.70x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.72x faster than Helium
- Ruby (3.4.9) is 1.06x faster than Helium
- Python (3.11.2) is 1.07x slower than Helium
- Perl (5.42.2) is 3.70x slower than Helium

