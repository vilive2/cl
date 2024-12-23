from datetime import datetime

from datetime import datetime, timedelta
import random

def get_random_date(start_date, end_date):
    """
    Generate a random date between start_date and end_date (inclusive).
    
    Args:
        start_date (str): The start of the date range, in "YYYY-MM-DD" format.
        end_date (str): The end of the date range, in "YYYY-MM-DD" format.
    
    Returns:
        str: A random date in "YYYY-MM-DD" format.
    """
    # Convert strings to datetime objects
    start = datetime.strptime(start_date, "%Y-%m-%d")
    end = datetime.strptime(end_date, "%Y-%m-%d")
    
    # Calculate the difference in days
    delta_days = (end - start).days
    
    # Generate a random number of days to add to the start date
    random_days = random.randint(0, delta_days)
    
    # Calculate the random date
    random_date = start + timedelta(days=random_days)
    
    # Return the random date as a string in "YYYY-MM-DD" format
    return random_date.date()

start_date = "1918-01-01"
end_date = "2024-12-31"

maxlen = 100

def gen(file):
    f = open(file, 'w')

    n = random.randint(1, maxlen)
    for _ in range(n):
        date = get_random_date(start_date, end_date)
        d = date.day
        m = date.month
        y = date.year
        f.write(f'{d} {m} {y}\n')

    f.close()


def is_date_in_range(given_date, start_date, end_date):
    """
    Check if a given date is between start_date and end_date (inclusive).
    
    Args:
        given_date (str): The date to check, in "YYYY-MM-DD" format.
        start_date (str): The start of the date range, in "YYYY-MM-DD" format.
        end_date (str): The end of the date range, in "YYYY-MM-DD" format.
    
    Returns:
        bool: True if given_date is within the range, False otherwise.
    """
    # Convert strings to datetime objects
    try:
        given_date = datetime.strptime(given_date, "%Y-%m-%d")
        start_date = datetime.strptime(start_date, "%Y-%m-%d")
        end_date = datetime.strptime(end_date, "%Y-%m-%d")
    except ValueError:
        print(given_date) 
    # Check if the date is within the range
    return start_date <= given_date <= end_date

#filter date range
start_date = "1996-11-19"
end_date = "2024-12-22"

def genout(infile, outfile):
    inf = open(infile, 'r')
    outf = open(outfile, 'w')

    other_dates = []
    while True:
        date = inf.readline().strip().split()

        if not date:
            break
        d = int(date[0])
        m = int(date[1])
        y = int(date[2])
        if is_date_in_range(f'{y:04}-{m:02}-{d:02}', start_date, end_date) :
            outf.write(f'{d:02}-{m:02}-{y:04}\n')
        else :
            other_dates.append(date)
    
    for date in other_dates:
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
