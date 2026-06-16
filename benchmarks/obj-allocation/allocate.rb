class Node
  def initialize(value, nxt)
    @value = value
    @next = nxt
  end
end

N = 1_000_000

head = nil

i = 0
while i < N
  head = Node.new(i, head)
  i += 1
end