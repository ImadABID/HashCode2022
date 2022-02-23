#include "ingredient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "ingredient.h"

void ingredient_init(int nbr_clients){
    ingredient_max_nbr = MAX_INGR_IN_PIZZA*nbr_clients;
    ingredient_names = malloc(ingredient_max_nbr * MAX_STR * sizeof(char));
}

void ingredient_free(){
    free(ingredient_names);
    ingredient_nbr = 0;
}

char *ingredient_get_name_by_id(int id){
    return ingredient_names+id*MAX_STR;
}

int ingredient_get_id_otherwise_add(char *ingredient_str){

    for(int i = 0; i < ingredient_nbr; i++){
        if(strcmp(ingredient_str, ingredient_get_name_by_id(i))==0){
            return i;
        }
    }

    strcpy(ingredient_get_name_by_id(ingredient_nbr), ingredient_str);
    ingredient_nbr++;

    return ingredient_nbr-1;

}

void ingredient_likes_hates(int *likes_nbr, int *hates_nbr, int ingredient_id){
    
    *likes_nbr = 0;
    *hates_nbr = 0;

    struct client client;
    for(int client_i = 0; client_i < clients_nbr; client_i++){
        
        client = clients[client_i];

        if(client_likes_ingredient(client, ingredient_id)){
            (*likes_nbr)++;
            continue;
        }

        if(client_hates_ingredient(client, ingredient_id)){
            (*hates_nbr)++;
        }

    }
}

void ingredient_likes_hates_for_set(int *likes_nbr, int *hates_nbr, int *ingredient_ids, int ingredient_ids_size){
    
    *likes_nbr = 0;
    *hates_nbr = 0;

    struct client client;
    for(int client_i = 0; client_i < clients_nbr; client_i++){
        
        client = clients[client_i];

        if(client_accept(client, ingredient_ids, ingredient_ids_size)){
            (*likes_nbr)++;
        }else{
            (*hates_nbr)++;
        }
    }
}

int ingredient_set_score(int *ingredient_ids, int ingredient_ids_size){
    int res = 0;

    struct client client;
    for(int client_i = 0; client_i < clients_nbr; client_i++){
        
        client = clients[client_i];

        if(client_accept_now(client, ingredient_ids, ingredient_ids_size)){
            res++;
        }
    }

    return res;
}