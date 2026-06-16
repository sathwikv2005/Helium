class Node:
    def __init__(self, value, next):
        self.value = value
        self.next = next


N = 1000000

head = None

i = 0
while i < N:
    head = Node(i, head)
    i += 1