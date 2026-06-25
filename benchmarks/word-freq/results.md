# Benchmark Results (word-freq)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./freq.he" target="_blank">Helium</a> | 0.770612 | 0.043896 | 1.00x (baseline) |
| <a href="./freq.py" target="_blank">Python (3.12.11)</a> | 0.819217 | 0.006242 | 1.06x slower |
| <a href="./freq.js" target="_blank">JavaScript (Node v26.3.0)</a> | 1.085323 | 0.005907 | 1.41x slower |
| <a href="./freq.rb" target="_blank">Ruby (3.4.9)</a> | 1.224373 | 0.003207 | 1.59x slower |
| <a href="./freq.pl" target="_blank">Perl (5.42.2)</a> | 1.485137 | 0.023948 | 1.93x slower |

---

## Helium Comparison
- Python (3.12.11) is 1.06x slower than Helium
- JavaScript (Node v26.3.0) is 1.41x slower than Helium
- Ruby (3.4.9) is 1.59x slower than Helium
- Perl (5.42.2) is 1.93x slower than Helium

