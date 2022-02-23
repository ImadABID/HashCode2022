#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "set.h"
#include "ingredient.h"

void set_init(){

    max_score = 0;
    ingredients_opt_len = 0;
    ingredients_opt = NULL;

    set_linklist_lent = 0;

    set_l1_nbr = 0;
    set_l1 = malloc(ingredient_nbr*sizeof(int));
    
    int l, h;
    int score;

    struct set *set_linklist_prev;
    set_linklist = NULL;
    
    for(int ingr = 0; ingr < ingredient_nbr; ingr++){
        ingredient_likes_hates(&l, &h, ingr);

        set_linklist_prev = set_linklist;

        set_linklist = malloc(sizeof(struct set));
        set_linklist->likes_nbr = l;
        set_linklist->hates_nbr = h;
        set_linklist->ingredients_nbr=1;
        set_linklist->ingredients[0] = ingr;

        if(l > h){
            set_l1[set_l1_nbr++] = ingr;
            set_linklist->freez = 0;

        }else{
            set_linklist->freez = 1;
            score = ingredient_set_score(set_linklist->ingredients, set_linklist->ingredients_nbr);
            if(score>max_score){
                max_score = score;
                ingredients_opt_len = set_linklist->ingredients_nbr;
                ingredients_opt = set_linklist->ingredients;
            }
        }

        set_linklist->prev = set_linklist_prev;

        set_linklist_lent++;
    }
}


void set_free(){
    free(set_l1);

    struct set *set_linklisy_act;
    while(set_linklist != NULL){


        set_linklisy_act = set_linklist;
        set_linklist = set_linklist->prev;
        free(set_linklisy_act);
        set_linklist_lent--;
    }

}

char set_clean(){

    char modif = 0;

    struct set *set_linklisy_next = NULL;
    struct set *set_linklisy_curs = set_linklist;
    while(set_linklisy_curs != NULL){
        if(set_linklisy_curs->freez &&  ingredients_opt != set_linklisy_curs->ingredients){
            
            set_linklist_lent--;

            modif = 1;

            if(set_linklisy_next==NULL){

                set_linklist = set_linklist->prev;
                free(set_linklisy_curs);
                set_linklisy_curs = set_linklist;

            }else{
                
                set_linklisy_next->prev = set_linklisy_curs->prev;
                free(set_linklisy_curs);
                set_linklisy_curs = set_linklisy_next->prev;

            }

        }else{
            set_linklisy_next = set_linklisy_curs;
            set_linklisy_curs = set_linklisy_curs->prev;
        }
    }

    return modif;

}

char set_extand(struct set *set, struct set *set_next){
    
    if(set->freez) return 0;

    struct set *new_entry;

    int l, h;
    char ele_added = 0;
    int score;

    for(
        int last_id = set->ingredients[set->ingredients_nbr-1]+1;
        last_id < ingredient_nbr;
        last_id++
    ){
        
        new_entry = malloc(sizeof(struct set));
        
        new_entry->ingredients_nbr = set->ingredients_nbr+1;
        memcpy(new_entry->ingredients, set->ingredients, set->ingredients_nbr*sizeof(int));
        new_entry->ingredients[set->ingredients_nbr] = last_id;

        ingredient_likes_hates_for_set(&l, &h, new_entry->ingredients, new_entry->ingredients_nbr);
        new_entry->likes_nbr = l;
        new_entry->hates_nbr = h;

        if(l>h){
            new_entry->freez = 0;
        }else{
            new_entry->freez = 1;
            score = ingredient_set_score(new_entry->ingredients, new_entry->ingredients_nbr);
            if(score > max_score){
                max_score = score;
                ingredients_opt_len = new_entry->ingredients_nbr;
                ingredients_opt = new_entry->ingredients;
            }else{
                free(new_entry);
                continue;
            }
        }

        if(set_next == NULL){
            new_entry->prev = set;
            set_linklist = new_entry;
        }else{
            set_next->prev = new_entry;
            new_entry->prev = set;
        }
        set_next = new_entry;

        ele_added = 1;

        set_linklist_lent++;

    }

    set->freez = 1;
    
    score = ingredient_set_score(new_entry->ingredients, new_entry->ingredients_nbr);
    if(score > max_score){
        max_score = score;
        ingredients_opt_len = set->ingredients_nbr;
        ingredients_opt = set->ingredients;
    }

    return ele_added;

}

char update(){

    char modif = set_clean();

    struct set *set_next = NULL;
    struct set *set = set_linklist;
    
    while(set != NULL && !modif){

        modif = set_extand(set, set_next);


        set_next = set;
        set = set->prev;

    }


    return modif;
}
