n = 1000000
prime = []

for i in 0..n
  prime.push(true)
end

prime[0] = false
prime[1] = false

i = 2
while i * i <= n
  if prime[i]
    j = i * i
    while j <= n
      prime[j] = false
      j += i
    end
  end
  i += 1
end

count = 0

for i in 0..n
  count += 1 if prime[i]
end

puts count