class Node {
	constructor(value) {
		this.value = value
		this.left = null
		this.right = null
	}

	insert(value) {
		if (value < this.value) {
			if (this.left === null) {
				this.left = new Node(value)
			} else {
				this.left.insert(value)
			}
		} else {
			if (this.right === null) {
				this.right = new Node(value)
			} else {
				this.right.insert(value)
			}
		}
	}

	sum() {
		let total = this.value

		if (this.left !== null) {
			total += this.left.sum()
		}

		if (this.right !== null) {
			total += this.right.sum()
		}

		return total
	}
}

const N = 100000

const root = new Node(50000)

let i = 0
while (i < N) {
	root.insert((i * 7919) % N)
	i++
}
