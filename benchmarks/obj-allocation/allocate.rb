class Node
  def initialize(value, nxt)
    @value = value
    @next = nxt
  end

  def sum
    total = 0
    current = self

    while !current.nil?
      total += current.instance_variable_get(:@value)
      current = current.instance_variable_get(:@next)
    end

    total
  end
end

N = 1_000_000

head = nil

i = 0
while i < N
  head = Node.new(i, head)
  i += 1
end