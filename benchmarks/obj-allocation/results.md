# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.127571 | 0.001750 | 3.72x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.362594 | 0.005842 | 1.31x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.475027 | 0.009540 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.12.11)</a> | 1.053393 | 0.009606 | 2.22x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.068290 | 0.008220 | 2.25x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 3.72x faster than Helium
- Ruby (3.4.9) is 1.31x faster than Helium
- Python (3.12.11) is 2.22x slower than Helium
- Perl (5.42.2) is 2.25x slower than Helium

