# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v20.19.1)</a> | 0.074984 | 0.001078 | 9.40x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.255670 | 0.005988 | 2.76x faster |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.453494 | 0.006631 | 1.55x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.704970 | 0.009512 | 1.00x (baseline) |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.801412 | 0.045826 | 1.14x slower |

---

## Helium Comparison
- JavaScript (Node v20.19.1) is 9.40x faster than Helium
- Ruby (3.4.9) is 2.76x faster than Helium
- Perl (5.42.2) is 1.55x faster than Helium
- Python (3.11.2) is 1.14x slower than Helium

