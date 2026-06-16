# Benchmark Results (obj-allocation)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./allocate.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.130040 | 0.003288 | 4.66x faster |
| <a href="./allocate.rb" target="_blank">Ruby (3.4.9)</a> | 0.367368 | 0.004626 | 1.65x faster |
| <a href="./allocate.he" target="_blank">Helium</a> | 0.605821 | 0.019434 | 1.00x (baseline) |
| <a href="./allocate.py" target="_blank">Python (3.11.2)</a> | 0.779564 | 0.007188 | 1.29x slower |
| <a href="./allocate.pl" target="_blank">Perl (5.42.2)</a> | 1.088545 | 0.021172 | 1.80x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 4.66x faster than Helium
- Ruby (3.4.9) is 1.65x faster than Helium
- Python (3.11.2) is 1.29x slower than Helium
- Perl (5.42.2) is 1.80x slower than Helium

