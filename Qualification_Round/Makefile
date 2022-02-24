all : main

main : main.c common.o skill.o contributor.o project.o
	gcc -g -Wall -o main main.c common.o skill.o contributor.o project.o

common.o : common.c common.h
	gcc -g -Wall -c common.c

skill.o : skill.c skill.h
	gcc -g -Wall -c skill.c

project.o : project.c project.h
	gcc -g -Wall -c project.c

contributor.o : contributor.c contributor.h
	gcc -g -Wall -c contributor.c


clean :
	rm -rf *.o src.zip main

zip :
	zip src.zip *.c *.h Makefile