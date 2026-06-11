# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.174425 | 0.008985 | 4.67x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.413563 | 0.003534 | 1.97x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.814429 | 0.012839 | 1.00x (baseline) |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.317895 | 0.048324 | 1.62x slower |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 1.472750 | 0.091753 | 1.81x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 4.67x faster than Helium
- Ruby (3.4.9) is 1.97x faster than Helium
- Perl (5.42.2) is 1.62x slower than Helium
- Python (3.11.2) is 1.81x slower than Helium

