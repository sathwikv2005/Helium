# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.076323 | 0.002325 | 4.21x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.296767 | 0.033083 | 1.08x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.321564 | 0.005400 | 1.00x (baseline) |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.455472 | 0.013526 | 1.42x slower |
| <a href="./loop.py" target="_blank">Python (3.12.11)</a> | 1.018415 | 0.049353 | 3.17x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 4.21x faster than Helium
- Ruby (3.4.9) is 1.08x faster than Helium
- Perl (5.42.2) is 1.42x slower than Helium
- Python (3.12.11) is 3.17x slower than Helium

