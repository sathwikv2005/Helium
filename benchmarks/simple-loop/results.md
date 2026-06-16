# Benchmark Results (simple-loop)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./loop.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.077591 | 0.003568 | 6.41x faster |
| <a href="./loop.rb" target="_blank">Ruby (3.4.9)</a> | 0.253003 | 0.006521 | 1.97x faster |
| <a href="./loop.pl" target="_blank">Perl (5.42.2)</a> | 0.459839 | 0.070496 | 1.08x faster |
| <a href="./loop.he" target="_blank">Helium</a> | 0.497431 | 0.004088 | 1.00x (baseline) |
| <a href="./loop.py" target="_blank">Python (3.11.2)</a> | 0.857330 | 0.072794 | 1.72x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 6.41x faster than Helium
- Ruby (3.4.9) is 1.97x faster than Helium
- Perl (5.42.2) is 1.08x faster than Helium
- Python (3.11.2) is 1.72x slower than Helium

