gcc -g -Wall /home/vivek/Documents/isi/courses/cl/cl/assignment/tcs/map-and-filter/test-temp-conv.c
for test in {1..10}
do
    echo "TEST $test"
    ./a.out < input-3-$test.txt | diff -bBw - output-3-$test.txt
done