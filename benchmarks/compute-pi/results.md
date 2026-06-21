# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.091829 | 0.014356 | 8.81x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 0.809144 | 0.045852 | 1.00x (baseline) |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.929120 | 0.044664 | 1.15x slower |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.992682 | 0.067104 | 2.46x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.167597 | 0.035095 | 2.68x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 8.81x faster than Helium
- Ruby (3.4.9) is 1.15x slower than Helium
- Python (3.11.2) is 2.46x slower than Helium
- Perl (5.42.2) is 2.68x slower than Helium

