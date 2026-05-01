const n = 10_000_000
const step = 1.0 / n
let sum = 0.0

for (let i = 0; i < n; i++) {
	const x = (i + 0.5) * step
	sum += 4.0 / (1.0 + x * x)
}

const pi = sum * step
console.log(pi)
