# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.092013 | 0.003106 | 18.07x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.881282 | 0.005206 | 1.89x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 1.662416 | 0.010887 | 1.00x (baseline) |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.944670 | 0.049605 | 1.17x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.094395 | 0.013064 | 1.26x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 18.07x faster than Helium
- Ruby (3.4.9) is 1.89x faster than Helium
- Python (3.11.2) is 1.17x slower than Helium
- Perl (5.42.2) is 1.26x slower than Helium

