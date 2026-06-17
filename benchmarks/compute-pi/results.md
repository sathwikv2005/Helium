# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.098183 | 0.005248 | 14.05x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.884882 | 0.015345 | 1.56x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 1.379810 | 0.005540 | 1.00x (baseline) |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.936810 | 0.072138 | 1.40x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.104985 | 0.010032 | 1.53x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 14.05x faster than Helium
- Ruby (3.4.9) is 1.56x faster than Helium
- Python (3.11.2) is 1.40x slower than Helium
- Perl (5.42.2) is 1.53x slower than Helium

