import random
# import nltk

# try:
#     nltk.data.find("corpora/words.zip")
# except LookupError:
#     nltk.download("words")

from nltk.corpus import words
word_list = words.words()

def gen(file):
    f = open(file, 'w')
    total_word = random.randint(1, 128)
    for _ in range(total_word):
        random_word = random.choice(word_list)
        f.write(f'{random_word}\n')
    f.close()

def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    words = inf.read().strip('\n').split('\n')

    for word in words:
        outf.write(word.upper()+"\n")
    inf.close()
    outf.close()

for i in range(1, 11, 1):
    gen(f'input-3-{i}.txt')
    genout(f'input-3-{i}.txt', f'output-3-{i}.txt')