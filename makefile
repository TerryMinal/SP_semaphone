control:
	gcc -g -o control control.c

main:
	gcc -g -o main main.c

all: control main
	control
	main
