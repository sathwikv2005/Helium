# Benchmark Results (sqrt)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.082034 | 0.006645 | 1.57x faster |
| <a href="./sqrt.he" target="_blank">Helium</a> | 0.129075 | 0.004516 | 1.00x (baseline) |
| <a href="./sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.238529 | 0.002979 | 1.85x slower |
| <a href="./sqrt.py" target="_blank">Python (3.11.2)</a> | 0.268735 | 0.010753 | 2.08x slower |
| <a href="./sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.283584 | 0.016376 | 2.20x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.57x faster than Helium
- Perl (5.42.2) is 1.85x slower than Helium
- Python (3.11.2) is 2.08x slower than Helium
- Ruby (3.4.9) is 2.20x slower than Helium

