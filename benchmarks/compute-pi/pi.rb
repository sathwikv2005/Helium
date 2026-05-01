n = 10_000_000
step = 1.0 / n
sum = 0.0

i = 0
while i < n
  x = (i + 0.5) * step
  sum += 4.0 / (1.0 + x * x)
  i += 1
end

pi = sum * step
puts pi