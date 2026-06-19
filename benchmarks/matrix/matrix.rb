n = 150

a = []
b = []
c = []

(0...n).each do |i|
  a << []
  b << []
  c << []

  (0...n).each do |j|
    a[i] << ((i + j) % 100)
    b[i] << ((i * j) % 100)
    c[i] << 0
  end
end

(0...n).each do |i|
  (0...n).each do |j|
    sum = 0

    (0...n).each do |k|
      sum += a[i][k] * b[k][j]
    end

    c[i][j] = sum
  end
end

puts c[0][0]
puts c[n - 1][n - 1]