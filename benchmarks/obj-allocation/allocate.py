class Node:
    def __init__(self, value, next):
        self.value = value
        self.next = next

    def sum(self):
        total = 0
        current = self

        while current is not None:
            total += current.value
            current = current.next

        return total


N = 1000000

head = None

i = 0
while i < N:
    head = Node(i, head)
    i += 1