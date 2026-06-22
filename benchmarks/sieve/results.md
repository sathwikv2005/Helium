# Benchmark Results (sieve)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.122890 | 0.005217 | 1.89x faster |
| <a href="./sieve.he" target="_blank">Helium</a> | 0.232848 | 0.006104 | 1.00x (baseline) |
| <a href="./sieve.py" target="_blank">Python (3.11.2)</a> | 0.361056 | 0.020779 | 1.55x slower |
| <a href="./sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.396278 | 0.020330 | 1.70x slower |
| <a href="./sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.494505 | 0.007606 | 2.12x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.89x faster than Helium
- Python (3.11.2) is 1.55x slower than Helium
- Ruby (3.4.9) is 1.70x slower than Helium
- Perl (5.42.2) is 2.12x slower than Helium

