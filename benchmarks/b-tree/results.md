# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.103651 | 0.007204 | 2.47x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.255600 | 0.016231 | 1.00x (baseline) |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.292778 | 0.039269 | 1.15x slower |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.328565 | 0.062163 | 1.29x slower |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 0.980609 | 0.036896 | 3.84x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.47x faster than Helium
- Ruby (3.4.9) is 1.15x slower than Helium
- Python (3.11.2) is 1.29x slower than Helium
- Perl (5.42.2) is 3.84x slower than Helium

