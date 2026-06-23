# Benchmark Results (word-freq)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./freq.he" target="_blank">Helium</a> | 0.776792 | 0.079934 | 1.00x (baseline) |
| <a href="./freq.py" target="_blank">Python (3.11.2)</a> | 0.796781 | 0.010146 | 1.03x slower |
| <a href="./freq.js" target="_blank">JavaScript (Node v26.3.0)</a> | 1.164688 | 0.048051 | 1.50x slower |
| <a href="./freq.rb" target="_blank">Ruby (3.4.9)</a> | 1.261303 | 0.019990 | 1.62x slower |
| <a href="./freq.pl" target="_blank">Perl (5.42.2)</a> | 1.556165 | 0.078716 | 2.00x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.03x slower than Helium
- JavaScript (Node v26.3.0) is 1.50x slower than Helium
- Ruby (3.4.9) is 1.62x slower than Helium
- Perl (5.42.2) is 2.00x slower than Helium

