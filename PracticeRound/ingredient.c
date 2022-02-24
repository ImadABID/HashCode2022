#include "ingredient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "ingredient.h"

void ingredient_init(int nbr_clients){
    ingredient_max_nbr = MAX_INGR_IN_PIZZA*nbr_clients;
    ingredient_names = malloc(ingredient_max_nbr * MAX_STR * sizeof(char));
    ingredient_nbr = 0;
}

void ingredient_init_gen(char **ingredient_names_new, int *ingredient_nbr_new, int *ingredient_max_nbr_new, int nbr_clients){
    *ingredient_max_nbr_new = MAX_INGR_IN_PIZZA*nbr_clients;
    *ingredient_names_new = malloc((*ingredient_max_nbr_new) * MAX_STR * sizeof(char));
    *ingredient_nbr_new = 0;
}

void ingredient_free(){
    free(ingredient_names);
    ingredient_nbr = 0;
}

void ingredient_free_gen(char *ingredient_names_new, int *ingredient_nbr_new){
    free(ingredient_names_new);
    *ingredient_nbr_new = 0;
}

char *ingredient_get_name_by_id(int id){
    return ingredient_names+id*MAX_STR;
}

char *ingredient_get_name_by_id_gen(char *ingredient_names_new, int id){
    return ingredient_names_new+id*MAX_STR;
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

int ingredient_get_id_otherwise_add_gen(char *ingredient_names_new, int *ingredient_nbr_new, char *ingredient_str){

    for(int i = 0; i < *ingredient_nbr_new; i++){
        if(strcmp(ingredient_str, ingredient_get_name_by_id_gen(ingredient_names_new, i))==0){
            return i;
        }
    }

    strcpy(ingredient_get_name_by_id_gen(ingredient_names_new, *ingredient_nbr_new), ingredient_str);
    (*ingredient_nbr_new)++;

    return (*ingredient_nbr_new)-1;

}

char ingredient_name_in_ingredient_id_list(char *ingredient_str, int *ingredient_ids, int ingredient_ids_size){
    
    for(int i = 0; i < ingredient_ids_size; i++){
        if(strcmp(ingredient_get_name_by_id(ingredient_ids[i]), ingredient_str) == 0){
            return 1;
        }
    }

    return 0;
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