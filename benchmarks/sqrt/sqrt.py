sum_ = 0.0

for n in range(1, 100001):
    x = n * 12345.6789
    guess = x

    for _ in range(20):
        guess = 0.5 * (guess + x / guess)

    sum_ += guess

print(sum_)