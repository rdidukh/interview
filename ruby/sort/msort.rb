#!/usr/bin/ruby -w

def msort(a, b, left, right)

  #printf("%i, %i\n", left, right)

  if left >= right-1
    return
  end

  middle = (right-left)/2 + left  

  #printf("1. msort(%i, %i)\n", left, middle)
  msort(a, b, left, middle)
  #printf("2. msort(%i, %i)\n", middle, right)
  msort(a, b, middle, right)  

  for j in left...right
    b[j] = a[j]
  end

  l = left
  i = left
  r = middle  

  while l < middle or r < right
    if l >= middle
      a[i] = b[r]
      r = r + 1
    elsif r >= right
      a[i] = b[l]
      l = l + 1
    elsif b[l] <= b[r]
      a[i] = b[l]
      l = l + 1
    elsif b[r] < b[l]
      a[i] = b[r]
      r = r + 1
    end  
    i = i + 1
  end
  
#  return A

end

if ARGV.length != 1
  puts "Argument error."
  exit 1
end

$N = ARGV[0].to_i

if $N < 1
  puts "Argument error." 
  exit 1
end

prng = Random.new(Time.now.to_i)

A = []

for i in 1..$N
  A.push prng.rand(2*$N)
end

puts A.join " "

msort(A, A.clone, 0, A.length)

puts A.join " "







