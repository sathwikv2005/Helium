class Node
  def initialize(value)
    @value = value
    @left = nil
    @right = nil
  end

  def insert(value)
    if value < @value
      if @left.nil?
        @left = Node.new(value)
      else
        @left.insert(value)
      end
    else
      if @right.nil?
        @right = Node.new(value)
      else
        @right.insert(value)
      end
    end
  end

  def sum
    total = @value

    unless @left.nil?
      total += @left.sum
    end

    unless @right.nil?
      total += @right.sum
    end

    total
  end
end

N = 100000

root = Node.new(50000)

i = 0
while i < N
  root.insert((i * 7919) % N)
  i += 1
end