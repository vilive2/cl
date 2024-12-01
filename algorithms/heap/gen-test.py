import random as rnd
f = open('fib-input.txt', 'w')
f.write('10\n')

l = ' '.join([str(rnd.randint(1, 200))  for _ in range(10)])
f.write(l+'\n')

# total operations
f.write('5\n')

# operations insert, min, ext-min, dec-key, delete
#             0       1      2        3       4
for i in range(5):
    optype = rnd.randint(0, 5) % 5
    f.write(str(optype)+' ')
    if optype in [0, 3]:
        key = rnd.randint(1, 200)
        f.write(str(key))
    f.write('\n')

f.close()