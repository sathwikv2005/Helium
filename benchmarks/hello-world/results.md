# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.024999 | 0.000630 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.045126 | 0.000796 | 1.81x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.048255 | 0.000834 | 1.93x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.072317 | 0.002571 | 2.89x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.145069 | 0.001787 | 5.80x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.81x slower than Helium
- Perl (5.42.2) is 1.93x slower than Helium
- JavaScript (Node v26.3.0) is 2.89x slower than Helium
- Ruby (3.4.9) is 5.80x slower than Helium

