class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def insert(self, value):
        if value < self.value:
            if self.left is None:
                self.left = Node(value)
            else:
                self.left.insert(value)
        else:
            if self.right is None:
                self.right = Node(value)
            else:
                self.right.insert(value)

    def sum(self):
        total = self.value

        if self.left is not None:
            total += self.left.sum()

        if self.right is not None:
            total += self.right.sum()

        return total


N = 100000

root = Node(50000)

i = 0
while i < N:
    root.insert((i * 7919) % N)
    i += 1