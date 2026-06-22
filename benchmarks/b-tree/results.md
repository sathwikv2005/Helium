# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.117470 | 0.012940 | 2.50x faster |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.287968 | 0.012740 | 1.02x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.294066 | 0.006923 | 1.00x (baseline) |
| <a href="./tree.py" target="_blank">Python (3.11.2)</a> | 0.335528 | 0.016613 | 1.14x slower |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 1.061351 | 0.036032 | 3.61x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.50x faster than Helium
- Ruby (3.4.9) is 1.02x faster than Helium
- Python (3.11.2) is 1.14x slower than Helium
- Perl (5.42.2) is 3.61x slower than Helium

