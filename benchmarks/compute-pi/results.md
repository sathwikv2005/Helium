# Benchmark Results (compute-pi)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./pi.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.102365 | 0.005465 | 7.73x faster |
| <a href="./pi.he" target="_blank">Helium</a> | 0.791643 | 0.013303 | 1.00x (baseline) |
| <a href="./pi.rb" target="_blank">Ruby (3.4.9)</a> | 0.935723 | 0.168135 | 1.18x slower |
| <a href="./pi.py" target="_blank">Python (3.11.2)</a> | 2.009823 | 0.121537 | 2.54x slower |
| <a href="./pi.pl" target="_blank">Perl (5.42.2)</a> | 2.144395 | 0.013082 | 2.71x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 7.73x faster than Helium
- Ruby (3.4.9) is 1.18x slower than Helium
- Python (3.11.2) is 2.54x slower than Helium
- Perl (5.42.2) is 2.71x slower than Helium

