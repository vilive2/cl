import random

maxm = 1024
maxk = 64
maxel = 100000
maxseqlen = 10000

def gen(file):
    f = open(file, 'w')

    m = random.randint(8, maxm)
    k = random.randint(1, min(m, maxk))

    f.write(f'{m} {k}\n')

    n = random.randint(1, maxseqlen)
    for _ in range(n):
        el = random.randint(0, maxel)
        f.write(f'{el}\n')

    f.close()

if __name__ == "__main__":
    for i in range(1, 11, 1):
        gen(f'input-4-{i}.txt')