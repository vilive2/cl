gcc -g -Wall /home/vivek/Documents/isi/courses/cl/cl/assignment/tcs/map-and-filter/test-prepend-prefix.c
for test in {1..10}
do
    echo "TEST $test"
    ./a.out < ../persons/output-3-$test.txt | diff -bBw - output-3-$test.txt
done