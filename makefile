control:
	gcc -g -o control control.c

main:
	gcc -g control.c -o main main.c

all: control main
	control
	main

clean:
	rm control
