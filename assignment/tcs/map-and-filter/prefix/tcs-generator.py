def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    while True:
        person = inf.readline().strip()

        if not person:
            break
        outf.write(f'Dear {person}\n')

    inf.close()
    outf.close()

if __name__ == "__main__":
    
    for i in range(1, 11, 1):
        infile = f'../persons/output-3-{i}.txt'
        outfile = f'output-3-{i}.txt'
        genout(infile, outfile)
