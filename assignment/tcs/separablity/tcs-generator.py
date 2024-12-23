import random

def randf(a, b):
    x = a + random.randint(0, int(b - a)) + random.random()
    return x

maxpoints = 10
maxcoord = 20
mincoord = -10

def gen(file):
    f = open(file, 'w')

    m = random.randint(2, maxpoints)
    f.write(f'{m}\n')

    prev = mincoord
    for _ in range(m):
        x = random.randint(prev, maxcoord)
        y = random.randint(mincoord, maxcoord)
        f.write(f'{x} {y}\n')
        prev = x

    n = random.randint(2, maxpoints)
    f.write(f'{n}\n')

    prev = mincoord
    for _ in range(n):
        x = random.randint(prev, maxcoord)
        y = random.randint(mincoord, maxcoord)
        f.write(f'{x} {y}\n')
        prev = x

    a = random.randint(mincoord, maxcoord)
    b = random.randint(a, maxcoord)
    f.write(f'{a} {b}\n')

if __name__ == "__main__":
    for i in range(1, 11, 1):
        gen(f'input-1-{i}.txt')