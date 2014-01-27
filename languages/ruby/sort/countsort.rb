#!/usr/bin/ruby -w

def sorted?(a)
  for i in 0...(a.length-1)
    if a[i] > a[i+1]
      return false
    end
  end
  return true
end

def equals?(a,b)
  h = {}

  for i in a
    h[i] = 0 unless h.has_key? i
    h[i] = h[i] + 1
  end
  
  for i in b
    return false unless h.has_key? i
    h[i] = h[i]-1 
    return false if h[i] < 0
  end

  for key,val in h
    return false if val != 0
  end

  return true

end

def countsort(a)

  max = a[0]
  for i in a
    max = i if i > max
  end  
  
  b = []  
  
  for i in 0..max
    b[i] = 0
  end

  for i in a
    b[i] = b[i] + 1
  end

  for i in 1...b.length
    b[i] = b[i] + b[i-1]
  end
  
  for i in 0...b.length
    b[i] = b[i]-1
  end

  c = []

  for i in 0...a.length
    c[b[a[i]]] = a[i]   
    b[a[i]] = b[a[i]] - 1
  end  

  return c

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

a = []

for i in 1..$N
  a.push prng.rand(2*$N)
end

puts a.join " "
b = a.clone
a = countsort(a)
puts a.join " "

print "Sorted... "
if sorted?(a)
  print "OK\n"
else
  print "FAIL\n"
end

print "Integrity... "
if equals?(a, b)
  print "OK\n"
else
  print "FAIL\n"
end


# puts A.join " "


