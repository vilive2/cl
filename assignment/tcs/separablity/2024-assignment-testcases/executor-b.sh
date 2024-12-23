gcc -g -Wall /home/vivek/Documents/isi/courses/cl/cl/assignment/area.c -lm

for test in {1..19}
do 
    echo "TEST $test"
    ./a.out < input1-$test.txt | diff -bBw - output5-$test.txt && echo "passed"
done