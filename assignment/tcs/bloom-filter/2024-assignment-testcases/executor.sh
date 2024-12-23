gcc -g -Wall /home/vivek/Documents/isi/courses/cl/cl/assignment/bloom-filter-vs-avl.c

for test in {1..5}
do 
    echo "TEST $test"
    ./a.out < input4-$test.txt | diff -bBw - output4-$test.txt
done