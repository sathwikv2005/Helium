sum = 0.0

(1..100000).each do |n|
  x = n * 12345.6789
  guess = x

  20.times do
    guess = 0.5 * (guess + x / guess)
  end

  sum += guess
end

puts sum