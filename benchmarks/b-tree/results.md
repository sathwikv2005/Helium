# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.099597 | 0.011326 | 2.44x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.242741 | 0.009198 | 1.00x (baseline) |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.247578 | 0.004998 | 1.02x slower |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.289926 | 0.006110 | 1.19x slower |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 0.970182 | 0.014811 | 4.00x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.44x faster than Helium
- Ruby (3.4.9) is 1.02x slower than Helium
- Python (3.11.2) is 1.19x slower than Helium
- Perl (5.42.2) is 4.00x slower than Helium

