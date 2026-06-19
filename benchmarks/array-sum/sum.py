arr = []

for i in range(1000000):
    arr.append(i)

s = 0

for i in range(1000000):
    s += arr[i]

print(s)