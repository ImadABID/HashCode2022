#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <unistd.h>

#include "client.h"
#include "ingredient.h"


int main(){

    clients_init_and_read_data();
    
    char buff[MAX_STR];
    next_word(buff);

    int nbr_ingr = atoi(buff);
    int ingr[nbr_ingr];

    for(int i = 0; i < nbr_ingr; i++){
        next_word(buff);
        ingr[i] = ingredient_get_id_otherwise_add(buff);
    }

    printf("score : %d\n", ingredient_set_score(ingr, nbr_ingr));

    clients_free();

    return 0;
}