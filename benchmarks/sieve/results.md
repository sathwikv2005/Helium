# Benchmark Results (sieve)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.102601 | 0.002171 | 2.10x faster |
| <a href="./sieve.he" target="_blank">Helium</a> | 0.215114 | 0.006416 | 1.00x (baseline) |
| <a href="./sieve.py" target="_blank">Python (3.11.2)</a> | 0.342832 | 0.017552 | 1.59x slower |
| <a href="./sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.348108 | 0.039668 | 1.62x slower |
| <a href="./sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.467573 | 0.020075 | 2.17x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.10x faster than Helium
- Python (3.11.2) is 1.59x slower than Helium
- Ruby (3.4.9) is 1.62x slower than Helium
- Perl (5.42.2) is 2.17x slower than Helium

