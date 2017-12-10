misc.o:
	gcc -c misc.c

sem.o:
	gcc -c sem.c

shm.o:
	gcc -c shm.c

control: sem.o shm.o misc.o
	gcc -g -o control control.c sem.o shm.o misc.o

main: sem.o shm.o misc.o
	gcc -g -o main main.c sem.o shm.o misc.o

all: control main
	control
	main

clean:
	rm control main
	rm *.o
