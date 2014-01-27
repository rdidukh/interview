#!/usr/bin/ruby -w

def max_subarray(a)
  len = a.length
  v = Array.new(len, 0)
  p = Array.new(len, -1)
  
  
  for i in 1...len
    for j in 0...i
      if a[i]-a[j]+v[j]>v[i]
        v[i] = a[i]-a[j]+v[j]
        p[i] = j
      end
    end
  end

  puts v.join(" ")
  puts p.join(" ")
  

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

max_subarray(A)








