# Benchmark Results (sqrt)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./sqrt.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.093182 | 0.015219 | 1.44x faster |
| <a href="./sqrt.he" target="_blank">Helium</a> | 0.133921 | 0.003629 | 1.00x (baseline) |
| <a href="./sqrt.pl" target="_blank">Perl (5.42.2)</a> | 0.234532 | 0.006113 | 1.75x slower |
| <a href="./sqrt.rb" target="_blank">Ruby (3.4.9)</a> | 0.278250 | 0.003217 | 2.08x slower |
| <a href="./sqrt.py" target="_blank">Python (3.12.11)</a> | 0.358106 | 0.008146 | 2.67x slower |

---

## Helium Comparison
- JavaScript (Node v26.3.0) is 1.44x faster than Helium
- Perl (5.42.2) is 1.75x slower than Helium
- Ruby (3.4.9) is 2.08x slower than Helium
- Python (3.12.11) is 2.67x slower than Helium

