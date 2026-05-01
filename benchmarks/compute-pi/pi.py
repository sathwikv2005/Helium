n = 10_000_000
step = 1.0 / n
s = 0.0

for i in range(n):
    x = (i + 0.5) * step
    s += 4.0 / (1.0 + x * x)

pi = s * step
print(pi)