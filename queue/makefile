a.out: queueMain.o queue.o
	gcc queueMain.o queue.o

queueMain.o: queueMain.c queue.h
	gcc -g -c queueMain.c

queue.o: queue.c queue.h
	gcc -g -c queue.c