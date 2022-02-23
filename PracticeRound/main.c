#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <unistd.h>

#include "client.h"
#include "ingredient.h"
#include "set.h"


//sig_handler
void print_tmp_data(int signum){
    printf("%d", ingredients_opt_len);
    for(int i = 0; i < ingredients_opt_len; i++){
        printf(" %s", ingredient_get_name_by_id(ingredients_opt[i]));
    }
    printf("\n");
    exit(0);
}


int main(){

    clients_init_and_read_data();

    set_init();

    //sig_handler
    signal(SIGINT, print_tmp_data); // Register signal handler

    int last_max_score = 0;
    while(update()){
        
        if(max_score != last_max_score){
            last_max_score = max_score;
            fprintf(stderr, "score=%d, pizza_nbr_ingr=%d, set_linklist_lent=%d\n", max_score, ingredients_opt_len, set_linklist_lent);
        }
    }

    printf("%d", ingredients_opt_len);
    for(int i = 0; i < ingredients_opt_len; i++){
        printf(" %s", ingredient_get_name_by_id(ingredients_opt[i]));
    }
    printf("\n");

    set_free();
    clients_free();

    return 0;
}