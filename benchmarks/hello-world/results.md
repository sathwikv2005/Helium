# Benchmark Results (hello-world)

## Summary

| Program | Median Time | Std Dev | vs Helium |
|--------|------------------|---------|-------------|
| <a href="./hello.he" target="_blank">Helium</a> | 0.024083 | 0.000655 | 1.00x (baseline) |
| <a href="./hello.py" target="_blank">Python (3.11.2)</a> | 0.044948 | 0.001670 | 1.87x slower |
| <a href="./hello.pl" target="_blank">Perl (5.42.2)</a> | 0.049455 | 0.002471 | 2.05x slower |
| <a href="./hello.js" target="_blank">JavaScript (Node v26.3.0)</a> | 0.073823 | 0.002002 | 3.07x slower |
| <a href="./hello.rb" target="_blank">Ruby (3.4.9)</a> | 0.159578 | 0.009906 | 6.63x slower |

---

## Helium Comparison
- Python (3.11.2) is 1.87x slower than Helium
- Perl (5.42.2) is 2.05x slower than Helium
- JavaScript (Node v26.3.0) is 3.07x slower than Helium
- Ruby (3.4.9) is 6.63x slower than Helium

