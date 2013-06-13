def isort(a)
 for i in 1...a.length
  j = i
  while j > 0 and a[j] < a[j-1]
   tmp = a[j]
   a[j] = a[j-1]
   a[j-1] = tmp
   j = j - 1
  end
 end
 return a
end

