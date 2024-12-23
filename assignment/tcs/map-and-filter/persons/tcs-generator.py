import random

common_first_names = [
    # Indian Male
    "Arjun", "Rohan", "Karthik", "Aditya", "Rajesh", "Pranav", "Suresh", "Vikram", "Harsha", "Manish",
    # Indian Female
    "Priya", "Aditi", "Kavya", "Meera", "Sneha", "Rhea", "Ananya", "Deepika", "Ishita", "Nandini",
    # Indian Gender-Neutral
    "Akash", "Anmol", "Arushi", "Tejas", "Samarth", "Dev", "Harini", "Nihar", "Shiv", "Tanmay",
    # American Male
    "James", "William", "Michael", "Ethan", "Mason", "Noah", "Jacob", "Benjamin", "Samuel", "Matthew",
    # American Female
    "Emma", "Olivia", "Ava", "Sophia", "Mia", "Harper", "Charlotte", "Ella", "Grace", "Madison",
    # American Gender-Neutral
    "Taylor", "Riley", "Jordan", "Casey", "Alex", "Avery", "Morgan", "Quinn", "Jamie", "Dakota"
]

common_last_names = [
    # Indian Last Names
    "Sharma", "Patel", "Singh", "Gupta", "Reddy", "Kumar", "Das", "Chopra", "Iyer", "Joshi",
    # American Last Names
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Martinez", "Anderson"
]

maxlen = 1000

def gen(file):
    f = open(file, 'w')

    n = random.randint(1, maxlen)
    for _ in range(n):
        firstname = random.choice(common_first_names)
        lastname = random.choice(common_last_names)
        age = random.randint(1, 100)
        f.write(f'{firstname} {lastname} {age}\n')

    f.close()

def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    while True:
        person = inf.readline().strip().split()

        if not person:
            break
        outf.write(f'{person[0]} {person[1]}\n')

    inf.close()
    outf.close()

if __name__ == "__main__":
    
    for i in range(1, 11, 1):
        infile = f'input-3-{i}.txt'
        outfile = f'output-3-{i}.txt'
        gen(infile)
        genout(infile, outfile)
