#include "ingredient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "ingredient.h"

void clients_init_and_read_data(){

    char buffer[MAX_STR];

    next_word(buffer);
    clients_nbr = atoi(buffer);

    ingredient_init(clients_nbr);

    clients = malloc(clients_nbr*sizeof(struct client));


    for(int i = 0; i < clients_nbr; i++){
        
        next_word(buffer);
        clients[i].conflcts_nbr = 0;
        clients[i].likes_nbr = atoi(buffer);
        clients[i].likes = malloc(clients[i].likes_nbr*sizeof(int));
        for(int j = 0; j < clients[i].likes_nbr; j++){
            next_word(buffer);
            clients[i].likes[j] = ingredient_get_id_otherwise_add(buffer);
            for(int pcli = 0; pcli < i; pcli++){
                if(ingredient_name_in_ingredient_id_list(buffer, clients[pcli].hates, clients[j].hates_nbr)){
                    clients[i].conflcts_nbr++;
                    clients[pcli].conflcts_nbr++;
                }
            }
        }

        next_word(buffer);
        clients[i].hates_nbr = atoi(buffer);
        clients[i].hates = malloc(clients[i].hates_nbr*sizeof(int));
        for(int j = 0; j < clients[i].hates_nbr; j++){
            next_word(buffer);
            clients[i].hates[j] = ingredient_get_id_otherwise_add(buffer);
            for(int pcli = 0; pcli < i; pcli++){
                if(ingredient_name_in_ingredient_id_list(buffer, clients[pcli].likes, clients[pcli].likes_nbr)){
                    clients[i].conflcts_nbr++;
                    clients[pcli].conflcts_nbr++;
                }
            }
        }

    }

}

void client_store_by_conflicts(){
    char modif = 1;
    struct client tmp_cl;
    int not_storted_yet_nbr = clients_nbr;
    while(modif){
        modif = 0;
        for(int i = 0; i < not_storted_yet_nbr-1; i++){
            if(clients[i].conflcts_nbr > clients[i+1].conflcts_nbr){
                modif = 1;
                tmp_cl = clients[i];
                clients[i] = clients[i+1];
                clients[i+1] = tmp_cl;
            }
        }
        not_storted_yet_nbr--;
    }
}

void clients_shrink_data(){

    client_store_by_conflicts();

    int ingredient_max_nbr_new;
    int ingredient_nbr_new;
    char *ingredient_names_new;

    int clients_nbr_shrinked;
    struct client *clients_new;

    if(clients_nbr > 100){
        clients_nbr_shrinked = (int)(0.5* clients_nbr);
    }else{
        clients_nbr_shrinked = clients_nbr;
    }
    
    ingredient_init_gen(&ingredient_names_new, &ingredient_nbr_new, &ingredient_max_nbr_new, clients_nbr_shrinked);

    clients_new = malloc(clients_nbr_shrinked*sizeof(struct client));


    for(int i = 0; i < clients_nbr_shrinked; i++){

        clients_new[i].likes_nbr = clients[i].likes_nbr;
        clients_new[i].likes = malloc(clients[i].likes_nbr*sizeof(int));
        for(int j = 0; j < clients[i].likes_nbr; j++){
            clients_new[i].likes[j] = ingredient_get_id_otherwise_add_gen(ingredient_names_new, &ingredient_nbr_new, ingredient_get_name_by_id(clients[i].likes[j]));
        }

        clients_new[i].hates_nbr = clients[i].hates_nbr;
        clients_new[i].hates = malloc(clients[i].hates_nbr*sizeof(int));
        for(int j = 0; j < clients[i].hates_nbr; j++){
            clients_new[i].hates[j] = ingredient_get_id_otherwise_add_gen(ingredient_names_new, &ingredient_nbr_new, ingredient_get_name_by_id(clients[i].hates[j]));
        }

    }

    clients_free();

    ingredient_max_nbr = ingredient_max_nbr_new;
    ingredient_nbr = ingredient_nbr_new;
    ingredient_names = ingredient_names_new;

    clients_nbr = clients_nbr_shrinked;
    clients = clients_new;
}

void clients_free(){
    for(int i = 0; i < clients_nbr; i++){
        free(clients[i].likes);
        free(clients[i].hates);
    }
    free(clients);

    ingredient_free();
}

char client_likes_ingredient(struct client client, int ingredient_id){
    for(int i=0; i< client.likes_nbr; i++){
        if(client.likes[i] == ingredient_id){
            return 1;
        }
    }

    return 0;
}

char client_hates_ingredient(struct client client, int ingredient_id){
    for(int i=0; i< client.hates_nbr; i++){
        if(client.hates[i] == ingredient_id){
            return 1;
        }
    }

    return 0;
}


char client_accept_now(struct client client, int *ingredient_ids, int ingredient_ids_size){
    
    int likes_cmpt = client.likes_nbr;

    char likes_ok = 0;

    for(int i = 0; i < ingredient_ids_size; i++){
        if(client_hates_ingredient(client, ingredient_ids[i])){
            return 0;
        }

        if(!likes_ok && client_likes_ingredient(client, ingredient_ids[i])){
            likes_cmpt--;
            if(likes_cmpt == 0){
                likes_ok = 1;
            }
        }
    }
    
    return likes_ok;
}

char client_accept(struct client client, int *ingredient_ids, int ingredient_ids_size){

    for(int i = 0; i < ingredient_ids_size; i++){
        if(client_hates_ingredient(client, ingredient_ids[i])){
            return 0;
        }
    }
    
    return 1;
}