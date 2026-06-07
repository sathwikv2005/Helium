# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.101127 | 0.002571 | 17.85x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.956859 | 0.023936 | 1.89x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 1.805096 | 0.042269 | 1.00x (baseline) |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 2.162942 | 0.112374 | 1.20x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.290999 | 0.082423 | 1.27x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 17.85x faster than Helium
- Ruby (3.4.9) is 1.89x faster than Helium
- Python (3.11.2) is 1.20x slower than Helium
- Perl (5.42.2) is 1.27x slower than Helium

