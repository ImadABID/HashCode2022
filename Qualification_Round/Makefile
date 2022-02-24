all : main

main : main.c common.o skill.o
	gcc -g -Wall -o main main.c common.o

common.o : common.c common.h
	gcc -g -Wall -c common.c

skill.o : skill.c skill.h
	gcc -g -Wall -c skill.c

clean :
	rm -rf *.o src.zip main

zip :
	zip src.zip *.c *.h Makefile