# Benchmark Results (b-tree)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./tree.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.108177 | 0.014762 | 2.39x faster |
| <a href="./tree.he" target="_blank">Helium</a> | 0.258815 | 0.011693 | 1.00x (baseline) |
| <a href="./tree.rb" target="_blank">Ruby (3.4.9)</a> | 0.300580 | 0.011291 | 1.16x slower |
| <a href="./tree.py" target="_blank">Python (3.12.11)</a> | 0.330939 | 0.027551 | 1.28x slower |
| <a href="./tree.pl" target="_blank">Perl (5.42.2)</a> | 1.105921 | 0.091767 | 4.27x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.39x faster than Helium
- Ruby (3.4.9) is 1.16x slower than Helium
- Python (3.12.11) is 1.28x slower than Helium
- Perl (5.42.2) is 4.27x slower than Helium

