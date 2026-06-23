# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099502 | 0.004194 | 2.51x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.249750 | 0.014090 | 1.00x (baseline) |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.266289 | 0.011776 | 1.07x slower |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.292103 | 0.004415 | 1.17x slower |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 0.978354 | 0.014830 | 3.92x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.51x faster than Helium
- Ruby (3.4.9) is 1.07x slower than Helium
- Python (3.11.2) is 1.17x slower than Helium
- Perl (5.42.2) is 3.92x slower than Helium

