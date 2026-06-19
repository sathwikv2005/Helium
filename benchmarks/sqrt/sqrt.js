let sum = 0

for (let n = 1; n <= 100000; n++) {
	let x = n * 12345.6789
	let guess = x

	for (let i = 0; i < 20; i++) {
		guess = 0.5 * (guess + x / guess)
	}

	sum += guess
}

console.log(sum)
