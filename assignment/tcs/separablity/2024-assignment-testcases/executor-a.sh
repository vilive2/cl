gcc -g -Wall /home/vivek/Documents/isi/courses/cl/cl/assignment/separablity-linear.c -lm

for test in {1..19}
do 
    echo "TEST $test"
    ./a.out < input1-$test.txt | diff -bBw - output1-$test.txt && echo "passed"
    # ./a.out < input1-$test.txt 
    # python3 ../line-utils.py input1-$test.txt
    # python3 ../line-utils.py input1-$test.txt | diff -bBw - output5-$test.txt
done