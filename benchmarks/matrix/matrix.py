N = 150

A = []
B = []
C = []

for i in range(N):
    A.append([])
    B.append([])
    C.append([])

    for j in range(N):
        A[i].append((i + j) % 100)
        B[i].append((i * j) % 100)
        C[i].append(0)

for i in range(N):
    for j in range(N):
        s = 0

        for k in range(N):
            s += A[i][k] * B[k][j]

        C[i][j] = s

print(C[0][0])
print(C[N - 1][N - 1])