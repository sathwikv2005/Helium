# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.086253 | 0.002059 | 19.28x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.889996 | 0.015846 | 1.87x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 1.663118 | 0.008472 | 1.00x (baseline) |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.958210 | 0.071368 | 1.18x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.113200 | 0.020348 | 1.27x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 19.28x faster than Helium
- Ruby (3.4.9) is 1.87x faster than Helium
- Python (3.11.2) is 1.18x slower than Helium
- Perl (5.42.2) is 1.27x slower than Helium

