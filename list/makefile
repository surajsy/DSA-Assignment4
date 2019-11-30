a.out: listMain.o list.o
	gcc listMain.o list.o

listMain.o: listMain.c list.h
	gcc -g -c listMain.c

list.o: list.c list.h
	gcc -g -c list.c