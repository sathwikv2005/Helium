# Benchmark Results (sieve)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sieve.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.107264 | 0.006557 | 1.90x faster |
| <a href="./sieve.he" target="_blank">Helium</a> | 0.204105 | 0.001312 | 1.00x (baseline) |
| <a href="./sieve.py" target="_blank">Python (3.11.2)</a> | 0.330755 | 0.013616 | 1.62x slower |
| <a href="./sieve.rb" target="_blank">Ruby (3.4.9)</a> | 0.344405 | 0.034278 | 1.69x slower |
| <a href="./sieve.pl" target="_blank">Perl (5.42.2)</a> | 0.455184 | 0.003895 | 2.23x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.90x faster than Helium
- Python (3.11.2) is 1.62x slower than Helium
- Ruby (3.4.9) is 1.69x slower than Helium
- Perl (5.42.2) is 2.23x slower than Helium

