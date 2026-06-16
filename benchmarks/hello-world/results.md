# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.025023 | 0.002039 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.046357 | 0.005080 | 1.85x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048966 | 0.000676 | 1.96x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.072725 | 0.002353 | 2.91x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.147044 | 0.001841 | 5.88x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.85x slower than Helium
- Perl (5.42.2) is 1.96x slower than Helium
- JavaScript (Node v26.3.0) is 2.91x slower than Helium
- Ruby (3.4.9) is 5.88x slower than Helium

