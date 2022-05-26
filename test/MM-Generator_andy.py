import random

n=5000
filename = 'okok'
maxcoor = 1000
file = open(filename+'.txt','w')
file.write(str(n)+"\n")
for i in range(n):
    r1=random.uniform(0,maxcoor)
    r2=random.uniform(0,maxcoor)
    file.write(f"{r1} {r2}\n")
file.close()
