const N = 150

const A = []
const B = []
const C = []

for (let i = 0; i < N; i++) {
	A.push([])
	B.push([])
	C.push([])

	for (let j = 0; j < N; j++) {
		A[i].push((i + j) % 100)
		B[i].push((i * j) % 100)
		C[i].push(0)
	}
}

for (let i = 0; i < N; i++) {
	for (let j = 0; j < N; j++) {
		let sum = 0

		for (let k = 0; k < N; k++) {
			sum += A[i][k] * B[k][j]
		}

		C[i][j] = sum
	}
}

console.log(C[0][0])
console.log(C[N - 1][N - 1])
