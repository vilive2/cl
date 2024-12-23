import random

maxlen = 10000

def gen(file):
    f = open(file, 'w')

    n = random.randint(1, maxlen)
    for _ in range(n):
        date = random.randint(1, 31)
        month = random.randint(1, 12)
        year = random.randint(1900, 2024)

        f.write(f'{date} {month} {year}\n')

    f.close()

def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    while True:
        date = inf.readline().strip().split()

        if not date:
            break
        d = int(date[0])
        m = int(date[1])
        y = int(date[2])
        outf.write(f'{d:02}-{m:02}-{y:04}\n')

    inf.close()
    outf.close()

if __name__ == "__main__":
    
    for i in range(1, 11, 1):
        infile = f'input-3-{i}.txt'
        outfile = f'output-3-{i}.txt'
        gen(infile)
        genout(infile, outfile)
