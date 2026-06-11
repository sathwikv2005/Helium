class Node {
	constructor(value, next) {
		this.value = value
		this.next = next
	}

	sum() {
		let total = 0
		let current = this

		while (current !== null) {
			total += current.value
			current = current.next
		}

		return total
	}
}

const N = 1000000

let head = null

let i = 0
while (i < N) {
	head = new Node(i, head)
	i++
}
