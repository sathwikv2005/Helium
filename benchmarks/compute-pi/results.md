# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.096174 | 0.004451 | 15.34x faster |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.885560 | 0.008531 | 1.67x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 1.475108 | 0.023629 | 1.00x (baseline) |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 1.914187 | 0.043404 | 1.30x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.117098 | 0.014851 | 1.44x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 15.34x faster than Helium
- Ruby (3.4.9) is 1.67x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium
- Perl (5.42.2) is 1.44x slower than Helium

