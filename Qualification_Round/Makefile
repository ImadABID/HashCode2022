all : main

main : main.c common.o
	gcc -g -Wall -o main main.c common.o

common.o : common.c common.h
	gcc -g -Wall -c common.c

clean :
	rm -rf *.o src.zip

zip :
	zip src.zip *.c *.h Makefile