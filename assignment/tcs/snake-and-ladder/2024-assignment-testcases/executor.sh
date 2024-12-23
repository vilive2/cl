gcc -g -Wall ../../../snake-and-ladder.c

for test in {1..18}
do
    echo "TEST $test"
    ./a.out < input2-$test.txt | diff -bBw - output2-$test.txt
done