#include "affectation.h"

#include "project.h"
#include "contributor.h"

void affectations_init(){
    affectations = malloc(project_tab_size * sizeof(struct affectation));
    affectations_size = 0;
}


void submition_file(){
    printf("%i\n",affectations_size);

    for (int i = 0; i < affectations_size;i++){

        
        printf("%s\n",project_tab[affectations[i].project_id].name);
        for(int j = 0; j < affectations[i].contributor_ids_size; j++){
            printf("%s ", contributor_tab[affectations[i].contributor_ids[j]].contributor_name);
        }
        printf("\n");
    }
}


void affectations_update(int t){

    int contributor_id;

    struct affectation *affectation;

    int start_time = 0;
    int end_time;

    int *skill_level;

    int req_level;

    char affected;

    for(int i=0; i < project_tab_size; i++){

        if(project_tab[i].affected || project_tab[i].skipped) continue;

        if(project_start_time_has_past(i, t)){
            project_tab[i].skipped = 1;
            project_tab_not_handled_yet_nbr--;
        }

        affected = 1;

        affectation = &(affectations[affectations_size]);

        (*affectation).project_id = i;
        (*affectation).contributor_ids_size = project_tab[i].roles_nbr;
        (*affectation).contributor_ids = malloc((*affectation).contributor_ids_size * sizeof(int));
        for(int role_i = 0; role_i < project_tab[i].roles_nbr; role_i++){
            
            req_level = contributor_find_the_best_level_at((*affectation).contributor_ids, role_i, project_tab[i].roles_id[role_i]);
            if(req_level >=  project_tab[i].roles_level[role_i]){
                req_level = project_tab[i].roles_level[role_i]-1;
            }else{
                req_level = project_tab[i].roles_level[role_i];
            }

            if(req_level == 0){
                req_level = 1;
            }
            
            contributor_id = skill_masters_get(project_tab[i].roles_id[role_i], req_level, (*affectation).contributor_ids, role_i, t);
            if(contributor_id == -1){
                free((*affectation).contributor_ids);
                affected = 0;
                break;
            }
            (*affectation).contributor_ids[role_i] = contributor_id;
            if(contributor_tab[contributor_id].available_after > start_time){
                start_time = contributor_tab[contributor_id].available_after;
            }
        }

        if(!affected) continue;

        project_tab[i].affected = 1;

        end_time = start_time + project_tab[(*affectation).project_id].duration;

        for(int j = 0; j < (*affectation).contributor_ids_size; j++){
            contributor_tab[(*affectation).contributor_ids[j]].available_after = end_time;

            skill_level = contributor_get_skill_level_ptr((*affectation).contributor_ids[j], project_tab[i].roles_id[j]);
            if(
                *skill_level == project_tab[i].roles_level[j] ||
                *skill_level == project_tab[i].roles_level[j] - 1
            ){
                (*skill_level)++;
            }
        }

        skill_masters_update_rank();

        affectations_size++;
        project_tab_not_handled_yet_nbr--;

    }
}