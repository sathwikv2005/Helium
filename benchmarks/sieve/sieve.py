n = 1000000
prime = []

for i in range(n + 1):
    prime.append(True)

prime[0] = False
prime[1] = False

i = 2
while i * i <= n:
    if prime[i]:
        j = i * i
        while j <= n:
            prime[j] = False
            j += i
    i += 1

count = 0

for i in range(n + 1):
    if prime[i]:
        count += 1

print(count)