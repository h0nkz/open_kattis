import sys
import random

testCases = int(sys.argv[1])
milk = int(sys.argv[2])
cats = int(sys.argv[3])

i = 0
t = 0

out = ""

out = out + "{} {}\n".format(milk, cats)
while i < cats:
    j = i + 1
    while j < cats:
        out = out + "{} {} {}\n".format(i, j, random.randint(1, 10))
        j = j + 1
    i = i + 1
    
f = open("graph-testdata.txt".format(cats), "w")
oneout = out
while t < testCases:
    out = out + oneout
    t = t + 1

lastout = "{}\n".format(testCases) + out

f.write(lastout)
f.close()
