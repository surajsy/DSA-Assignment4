a.out: stackMain.o stack.o
	gcc stackMain.o stack.o

stackMain.o: stackMain.c stack.h
	gcc -g -c stackMain.c

stack.o: stack.c stack.h
	gcc -g -c stack.c