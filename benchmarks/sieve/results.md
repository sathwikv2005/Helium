# Benchmark Results (sieve)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.100431 | 0.001387 | 2.17x faster |
| <a href="./sieve.he" target="_blank">Helium</a> | 0.218172 | 0.003212 | 1.00x (baseline) |
| <a href="./sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.330016 | 0.005800 | 1.51x slower |
| <a href="./sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.450743 | 0.007226 | 2.07x slower |
| <a href="./sieve.py" target="_blank">Python (3.12.11)</a> | 0.548667 | 0.014601 | 2.51x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 2.17x faster than Helium
- Ruby (3.4.9) is 1.51x slower than Helium
- Perl (5.42.2) is 2.07x slower than Helium
- Python (3.12.11) is 2.51x slower than Helium

