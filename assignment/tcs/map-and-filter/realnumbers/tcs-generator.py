import random

maxlen = 100000
maxnum = 100
minnum = -100

def randreal(a, b):
    return random.randint(a, b-1) + random.random()

def gen(file):
    f = open(file, 'w')
    n = random.randint(1, maxlen)
    for _ in range(n):
        num = randreal(minnum, maxnum)
        f.write(f'%.4f\n'%num)

    f.close()

def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    nums = inf.read().strip().split()

    for num in nums :
        outnm = float(num) * 9/5 + 32
        outf.write(f'%.4f\n'%outnm)

    inf.close()
    outf.close()

if __name__ == "__main__":
    for i in range(1, 11, 1):
        gen(f'input-3-{i}.txt')
        genout(f'input-3-{i}.txt', f'output-3-{i}.txt')