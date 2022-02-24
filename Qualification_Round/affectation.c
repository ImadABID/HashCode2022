#include "affectation.h"

#include "project.h"
#include "contributor.h"

void affectations_init(){
    affectations = malloc(project_tab_size * sizeof(struct affectation));
    affectations_size = 0;
}

void affectations_update(int t){

    int contributor_id;
    int start_time = 0;

    for(int i=0; i < project_tab_size; i++){

        if(project_tab[i].affected) continue;

        affectations[i].project_id = i;
        affectations[i].contributor_ids_size = project_tab[i].roles_nbr;
        affectations[i].contributor_ids = malloc(affectations[i].contributor_ids_size * sizeof(int));
        for(int role_i = 0; role_i < project_tab[i].roles_nbr; role_i++){
            contributor_id = skill_masters_get(project_tab[i].roles_id[role_i], project_tab[i].roles_level[role_i], t);
            if(contributor_id == -1){
                free(affectations[i].contributor_ids);
                continue;
            }
            affectations[i].contributor_ids[role_i] = contributor_id;
            if(contributor_tab[contributor_id].available_after > start_time){
                start_time = contributor_tab[contributor_id].available_after;
            }
        }

        affectations[i].start_time = start_time;

        for(int i = 0; i < affectations[i].contributor_ids_size; i++){
            contributor_tab[affectations[i].contributor_ids[i]].available_after = affectations[i].start_time + project_tab[affectations[i].project_id].duration;
        }

    }
}