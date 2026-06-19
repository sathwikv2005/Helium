# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099119 | 0.003689 | 2.77x faster |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.243012 | 0.005863 | 1.13x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.274237 | 0.009772 | 1.00x (baseline) |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.283514 | 0.004950 | 1.03x slower |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 0.996549 | 0.064001 | 3.63x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.77x faster than Helium
- Ruby (3.4.9) is 1.13x faster than Helium
- Python (3.11.2) is 1.03x slower than Helium
- Perl (5.42.2) is 3.63x slower than Helium

