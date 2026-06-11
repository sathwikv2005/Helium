# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.114557 | 0.003678 | 3.93x faster |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.275047 | 0.003666 | 1.64x faster |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.373132 | 0.010651 | 1.21x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.450567 | 0.012683 | 1.00x (baseline) |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 1.087304 | 0.011909 | 2.41x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 3.93x faster than Helium
- Ruby (3.4.9) is 1.64x faster than Helium
- Python (3.11.2) is 1.21x faster than Helium
- Perl (5.42.2) is 2.41x slower than Helium

