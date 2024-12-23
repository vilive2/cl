import random

# import nltk

# try:
#     nltk.data.find("corpora/words.zip")
# except LookupError:
#     nltk.download("words")

from nltk.corpus import words
word_list = words.words()

domains = ["yahoo.com", "gmail.com", "outlook.com", "xmail.com", "email.com", "hotmail.com", "wiz.com", "amazon.com"]

maxlen = 100

def gen(file):
    f = open(file, 'w')
    filter_domain = random.choice(domains)
    f.write(f'{filter_domain}\n')
    
    total_email = random.randint(1, maxlen)
    for _ in range(total_email):
        random_word = random.choice(word_list)
        domain = random.choice(domains)
        f.write(f'{random_word}@{domain}\n')
    f.close()

def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    filter_domain = inf.readline().strip()
    other_mails = []
    while True:
        email = inf.readline().strip()
        if not email:
            break
        
        if email.endswith(filter_domain) :
            outf.write(f'{email}\n')
        else :
            other_mails.append(email)
    for email in other_mails:
        outf.write(f'{email}\n')
    inf.close()
    outf.close()

for i in range(1, 11, 1):
    gen(f'input-3-{i}.txt')
    genout(f'input-3-{i}.txt', f'output-3-{i}.txt')