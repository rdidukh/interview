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

def heapsort(a)
  for i in 0...a.length
    j = i
    p = (j-1)/2
    while j > 0 and a[j] > a[p]
      tmp = a[j]
      a[j] = a[p]
      a[p] = tmp
      j = p
      p = (j-1)/2
    end 
  end

  for i in (a.length-1).downto(0)  
    tmp = a[0]
    a[0] = a[i]
    a[i] = tmp
    
    j = 0

    while j < i
      m = j
      m = 2*j+1 if 2*j+1 < i and a[2*j+1] > a[m] 
      m = 2*j+2 if 2*j+2 < i and a[2*j+2] > a[m]
      break if m == j

      tmp = a[j]
      a[j] = a[m]
      a[m] = tmp

      j = m

    end

  end

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
heapsort(a)
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


