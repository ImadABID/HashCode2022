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
    int start_time = 0;

    char affected;

    for(int i=0; i < project_tab_size; i++){

        if(project_tab[i].affected) continue;

        affected = 1;

        affectations[affectations_size].project_id = i;
        affectations[affectations_size].contributor_ids_size = project_tab[i].roles_nbr;
        affectations[affectations_size].contributor_ids = malloc(affectations[affectations_size].contributor_ids_size * sizeof(int));
        for(int role_i = 0; role_i < project_tab[i].roles_nbr; role_i++){
            contributor_id = skill_masters_get(project_tab[i].roles_id[role_i], project_tab[i].roles_level[role_i], t);
            if(contributor_id == -1){
                free(affectations[affectations_size].contributor_ids);
                affected = 0;
                break;
            }
            affectations[affectations_size].contributor_ids[role_i] = contributor_id;
            if(contributor_tab[contributor_id].available_after > start_time){
                start_time = contributor_tab[contributor_id].available_after;
            }
        }

        if(!affected) continue;

        project_tab[i].affected = 1;

        affectations[affectations_size].start_time = start_time;

        for(int j = 0; j < affectations[affectations_size].contributor_ids_size; j++){
            contributor_tab[affectations[affectations_size].contributor_ids[j]].available_after = affectations[affectations_size].start_time + project_tab[affectations[affectations_size].project_id].duration;
        }

        affectations_size++;

    }
}