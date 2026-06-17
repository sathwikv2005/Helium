class Node {
	constructor(value, next) {
		this.value = value
		this.next = next
	}
}

const N = 1000000

let head = null

let i = 0
while (i < N) {
	head = new Node(i, head)
	i++
}
