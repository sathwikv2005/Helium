arr = []

for i in 0...1000000
  arr.push(i)
end

sum = 0

for i in 0...1000000
  sum += arr[i]
end

puts sum