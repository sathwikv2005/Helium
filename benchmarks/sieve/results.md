# Benchmark Results (sieve)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.104581 | 0.002329 | 2.04x faster |
| <a href="./sieve.he" target="_blank">Helium</a> | 0.213835 | 0.002920 | 1.00x (baseline) |
| <a href="./sieve.py" target="_blank">Python (3.11.2)</a> | 0.333681 | 0.020522 | 1.56x slower |
| <a href="./sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.336831 | 0.006400 | 1.58x slower |
| <a href="./sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.453912 | 0.010120 | 2.12x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.04x faster than Helium
- Python (3.11.2) is 1.56x slower than Helium
- Ruby (3.4.9) is 1.58x slower than Helium
- Perl (5.42.2) is 2.12x slower than Helium

