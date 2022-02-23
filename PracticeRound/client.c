#include "ingredient.h"
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
        clients[i].likes_nbr = atoi(buffer);
        clients[i].likes = malloc(clients[i].likes_nbr*sizeof(int));
        for(int j = 0; j < clients[i].likes_nbr; j++){
            next_word(buffer);
            clients[i].likes[j] = ingredient_get_id_otherwise_add(buffer);
        }

        next_word(buffer);
        clients[i].hates_nbr = atoi(buffer);
        clients[i].hates = malloc(clients[i].hates_nbr*sizeof(int));
        for(int j = 0; j < clients[i].hates_nbr; j++){
            next_word(buffer);
            clients[i].hates[j] = ingredient_get_id_otherwise_add(buffer);
        }

    }

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