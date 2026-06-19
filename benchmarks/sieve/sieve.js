const n = 1000000
const prime = []

for (let i = 0; i <= n; i++) {
	prime.push(true)
}

prime[0] = false
prime[1] = false

for (let i = 2; i * i <= n; i++) {
	if (prime[i]) {
		for (let j = i * i; j <= n; j += i) {
			prime[j] = false
		}
	}
}

let count = 0

for (let i = 0; i <= n; i++) {
	if (prime[i]) count++
}

console.log(count)
