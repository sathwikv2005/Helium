# Benchmark Results (word-freq)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./freq.py" target="_blank">Python (3.11.2)</a> | 0.925295 | 0.081383 | 1.06x faster |
| <a href="./freq.he" target="_blank">Helium</a> | 0.979589 | 0.026484 | 1.00x (baseline) |
| <a href="./freq.js" target="_blank">JavaScript (Node v26.3.0)</a> | 1.316953 | 0.068527 | 1.34x slower |
| <a href="./freq.rb" target="_blank">Ruby (3.4.9)</a> | 1.439344 | 0.041587 | 1.47x slower |
| <a href="./freq.pl" target="_blank">Perl (5.42.2)</a> | 1.802743 | 0.043219 | 1.84x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.06x faster than Helium
- JavaScript (Node v26.3.0) is 1.34x slower than Helium
- Ruby (3.4.9) is 1.47x slower than Helium
- Perl (5.42.2) is 1.84x slower than Helium

