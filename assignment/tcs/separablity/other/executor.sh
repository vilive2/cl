gcc -g -Wall /home/vivek/Documents/isi/courses/cl/cl/assignment/separablity-linear.c -lm

for test in {1..6}
do 
    echo "TEST $test"
    # ./a.out < input-1-$test.txt | diff -bBw - output-1-$test.txt
    ./a.out < input-1-$test.txt 
    python3 ../line-utils.py input-1-$test.txt
done