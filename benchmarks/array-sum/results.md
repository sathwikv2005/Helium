# Benchmark Results (array-sum)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sum.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.094303 | 0.003084 | 1.35x faster |
| <a href="./sum.he" target="_blank">Helium</a> | 0.127691 | 0.001688 | 1.00x (baseline) |
| <a href="./sum.pl" target="_blank">Perl (5.42.2)</a> | 0.235573 | 0.005429 | 1.84x slower |
| <a href="./sum.py" target="_blank">Python (3.11.2)</a> | 0.238980 | 0.007218 | 1.87x slower |
| <a href="./sum.rb" target="_blank">Ruby (3.4.9)</a> | 0.379693 | 0.131756 | 2.97x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.35x faster than Helium
- Perl (5.42.2) is 1.84x slower than Helium
- Python (3.11.2) is 1.87x slower than Helium
- Ruby (3.4.9) is 2.97x slower than Helium

