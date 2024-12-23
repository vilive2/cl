import random

def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    other_persons = []
    while True:
        person = inf.readline().strip().split()

        if not person:
            break
        if int(person[2]) > 60 :
            outf.write(f'{person[0]} {person[1]} {person[2]}\n')
        else :
            other_persons.append(person)

    for person in other_persons:
        outf.write(f'{person[0]} {person[1]} {person[2]}\n')

    inf.close()
    outf.close()

if __name__ == "__main__":
    
    for i in range(1, 11, 1):
        infile = f'../persons/input-3-{i}.txt'
        outfile = f'output-3-{i}.txt'
        genout(infile, outfile)
