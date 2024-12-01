stl.a: avl/avl.o avl/rotation.o avl/utils.o heap/heap.o list/list.o map/map.o queue/queue.o stack/stack.o
	rm ../stl/*.a || true
	rm ../stl/*.h
	cp */*.h ../stl/
	ar cr ../stl/stl.a */*.o

avl/avl.o: avl/avl.h avl/avl.c
	gcc -o avl/avl.o -c avl/avl.c

avl/rotation.o: avl/avl.h avl/rotation.c
	gcc -o avl/rotation.o -c avl/rotation.c

avl/utils.o: avl/avl.h avl/utils.c
	gcc -o avl/utils.o -c avl/utils.c

heap/heap.o: heap/heap.h heap/heap.c
	gcc -o heap/heap.o -c heap/heap.c

list/list.o: list/list.h list/list.c
	gcc -o list/list.o -c list/list.c

map/map.o: map/map.h map/map.c
	gcc -o map/map.o -c map/map.c

queue/queue.o: queue/queue.h queue/queue.c
	gcc -o queue/queue.o -c queue/queue.c

stack/stack.o: stack/stack.h stack/stack.c
	gcc -o stack/stack.o -c stack/stack.c

clean:
	rm */*.o