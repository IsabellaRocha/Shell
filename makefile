all: main.o shell.o
	gcc -o program main.o shell.o

main.o: main.c headers.h
	gcc -c main.c

shell.o: shell.c headers.h
	gcc -c shell.c

run:
	./program

check: main.c shell.c headers.h
	gcc -g main.c shell.c

gdb:
	gdb program.exe

clean:
	rm *.o
	rm *.exe
