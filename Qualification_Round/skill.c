#include "skill.h"
#include "common.h"
#include "contributor.h"

#define MAX_SKILL_MASTERS 10000
#define MAX_SKILL_TO_UPDATE_QIUE 100

int skill_masters_last_proposed_index;
int skill_masters_last_proposed_skill_ids[MAX_SKILL_TO_UPDATE_QIUE];
int skill_masters_last_proposed_indexs[MAX_SKILL_TO_UPDATE_QIUE];

void skill_init(){
    skill_nbr = 0;

    skill_masters_last_proposed_index = 0;
}

char *skill_get_name_by_id(int id){
    return skills_name+id*MAX_STR;
}

int skill_get_id_otherwise_add(char *skill_str){

    for(int i = 0; i < skill_nbr; i++){
        if(strcmp(skill_str, skill_get_name_by_id(i))==0){
            return i;
        }
    }

    strcpy(skill_get_name_by_id(skill_nbr), skill_str);
    skill_nbr++;

    return skill_nbr-1;

}

void skill_masters_init(){
    skill_masters = malloc(skill_nbr * sizeof(int *));
    skill_masters_indexes = malloc(skill_nbr * sizeof(int));
    for(int i = 0; i<skill_nbr; i++){
        skill_masters[i] = malloc(MAX_SKILL_MASTERS * sizeof(int));
        skill_masters_indexes[i] = 0;
    }
}

void skill_masters_free(){
    
    for(int i = 0; i<skill_nbr; i++){
        free(skill_masters[i]);
    }

    free(skill_masters);
    free(skill_masters_indexes);

}

void skill_masters_populate(){
    int skill_tab_index;
    for(int contributor_i = 0; contributor_i<contributor_tab_size; contributor_i++){
        for(int skill_i = 0; skill_i<contributor_tab[contributor_i].skills_nbre; skill_i++){
            skill_tab_index = contributor_tab[contributor_i].skills_id[skill_i];
            skill_masters[skill_tab_index][skill_masters_indexes[skill_tab_index]] = contributor_i;
            skill_masters_indexes[skill_tab_index]++;
        }
    }
}

void skill_masters_store_by_level(int skill_id, int *masters_ids, int masters_ids_size){
    char modif = 1;
    struct contributor tmp;
    int not_storted_yet_nbr = masters_ids_size;
    while(modif){
        modif = 0;
        for(int i = 0; i < not_storted_yet_nbr-1; i++){
            if(contributor_tab[i].skills_level[skill_id] > contributor_tab[i+1].skills_level[skill_id]){
                modif = 1;
                tmp = contributor_tab[i];
                contributor_tab[i] = contributor_tab[i+1];
                contributor_tab[i+1] = tmp;
            }
        }
        not_storted_yet_nbr--;
    }
}


void skill_masters_reindexetion(){
    for(int i = 0; i<skill_nbr; i++){
        
        skill_masters_store_by_level(i, skill_masters[i], skill_masters_indexes[i]);
        
    }
}

char contributor_in_list(int contibutor_id, int *contibutor_ids, int contibutor_ids_size){
    for(int i = 0; i<contibutor_ids_size; i++){
        if(contibutor_id == contibutor_ids[i]){
            return 1;
        }
    }
    return 0;
}

int skill_masters_get(int skill_id, int skill_level, int *contibutor_id_not_int, int contibutor_id_not_int_size, int t){
    int contr_id;
    for(int i = 0; i<skill_masters_indexes[skill_id]; i++){
        contr_id=skill_masters[skill_id][i];
        if(
            contributor_get_skill_level(contr_id, skill_id) >= skill_level &&
            contributor_is_available(contr_id,t) &&
            !contributor_in_list(contr_id, contibutor_id_not_int, contibutor_id_not_int_size)
        ){
            if(skill_masters_last_proposed_index < MAX_SKILL_TO_UPDATE_QIUE){
                skill_masters_last_proposed_skill_ids[skill_masters_last_proposed_index] = skill_id;
                skill_masters_last_proposed_indexs[skill_masters_last_proposed_index] = contr_id;
                skill_masters_last_proposed_index++;
            }

            return contr_id;
        }
    }

    return -1;
}

void skill_masters_update_rank_for_one(int skill_id, int constri_rank){
    int tmp;
    int contr_level;
    int next_contr_level;
    if(constri_rank < skill_masters_indexes[skill_id]-1){
        contr_level = contributor_get_skill_level(skill_masters[skill_id][constri_rank], skill_id);
        next_contr_level = contributor_get_skill_level(skill_masters[skill_id][constri_rank+1], skill_id);
        if(contr_level > next_contr_level){
            tmp = skill_masters[skill_id][constri_rank];
            skill_masters[skill_id][constri_rank]
                = skill_masters[skill_id][constri_rank+1];
            skill_masters[skill_id][constri_rank+1] = tmp;
        }
    }
}

void skill_masters_update_rank(){
    for(int i = 0; i<skill_masters_last_proposed_index; i++){
        skill_masters_update_rank_for_one(
            skill_masters_last_proposed_skill_ids[i],
            skill_masters_last_proposed_indexs[i]
        );
    }
    skill_masters_last_proposed_index = 0;
}