# Benchmark Results (sieve)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.107789 | 0.016321 | 2.31x faster |
| <a href="./sieve.he" target="_blank">Helium</a> | 0.249035 | 0.004295 | 1.00x (baseline) |
| <a href="./sieve.py" target="_blank">Python (3.11.2)</a> | 0.324988 | 0.005367 | 1.30x slower |
| <a href="./sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.335447 | 0.007451 | 1.35x slower |
| <a href="./sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.450238 | 0.004657 | 1.81x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.31x faster than Helium
- Python (3.11.2) is 1.30x slower than Helium
- Ruby (3.4.9) is 1.35x slower than Helium
- Perl (5.42.2) is 1.81x slower than Helium

