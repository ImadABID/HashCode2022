all : main

compute_score : compute_score.c client.o ingredient.o common.o set.o
	gcc -g -Wall -o compute_score compute_score.c client.o ingredient.o common.o set.o

main : main.c client.o ingredient.o common.o set.o
	gcc -g -Wall -o main main.c client.o ingredient.o common.o set.o

set.o : set.c set.h
	gcc -g -Wall -c set.c 

client.o : client.c client.h
	gcc -g -Wall -c client.c

ingredient.o : ingredient.c ingredient.h
	gcc -g -Wall -c ingredient.c

common.o : common.c common.h
	gcc -g -Wall -c common.c

clean :
	rm -rf *.o src.zip

zip :
	zip src.zip *.c *.h Makefile