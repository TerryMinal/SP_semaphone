.PHONY: main control 

main: sem.o shm.o misc.o
	gcc -g -o main main.c sem.o shm.o misc.o

control: sem.o shm.o misc.o
	gcc -g -o control control.c sem.o shm.o misc.o

misc.o:
	gcc -c misc.c

sem.o:
	gcc -c sem.c

shm.o:
	gcc -c shm.c

all: control main
	control
	main

clean:
	rm control main *.o story
