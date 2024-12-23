import random

max_player = 10
max_board_size = 10
max_ladder = 5
max_snake = 5
max_round = 50

def gen(file):
    f = open(file, 'w')
    k = random.randint(1, max_player)
    m = random.randint(1, max_board_size)
    n = random.randint(1, max_board_size)
    l = random.randint(1, max_ladder)
    s = random.randint(1, max_snake)
    r = random.randint(1, max_round)

    f.write(f'{k} {m} {n} {l} {s} {r}\n')

    for _ in range(l):
        ladder_start = random.randint(1, m * n)
        ladder_end = random.randint(ladder_start, m * n)
        f.write(f'{ladder_start} {ladder_end}\n')

    for _ in range(s):
        snake_start = random.randint(1, m * n)
        snake_end = random.randint(1, snake_start)
        f.write(f'{snake_start} {snake_end}\n')

    for _ in range(r):
        for __ in range(k):
            roll = random.randint(1, 12)
            f.write(f'{roll} ')
        f.write('\n')

    f.close()

if __name__ == "__main__":
    for i in range(1, 10, 1):
        gen(f'input-2-{i}.txt')