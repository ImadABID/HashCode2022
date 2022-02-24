#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <unistd.h>

#include "project.h"
#include "skill.h"

int project_tab_size;
struct  project* project_tab;

void project_read_data(){

    char str[MAX_STR];

    project_tab = malloc(project_tab_size*sizeof(struct project));

    for(int i = 0; i< project_tab_size-1; i++){
        
        next_word(str);
        strcpy(project_tab[i].name,str);

        next_word(str);
        project_tab[i].duration = atoi(str);

        next_word(str);
        project_tab[i].best_befor = atoi(str);

        next_word(str);
        project_tab[i].score = atoi(str);

        next_word(str);
        project_tab[i].roles_nbr = atoi(str);

        project_tab[i].roles_id = malloc(project_tab[i].roles_nbr*sizeof(int));
        for(int j = 0; j< project_tab[i].roles_nbr-1;j++){
            next_word(str);
            project_tab[i].roles_id[j] = skill_get_id_otherwise_add(str);
            next_word(str);
            project_tab[i].roles_level[j] = atoi(str);
        }
    }

}

void project_store_by_bestbefore(struct  project* project_tab){
    char modif = 1;
    struct project tmp_cl;
    int not_storted_yet_nbr = project_tab_size;
    while(modif){
        modif = 0;
        for(int i = 0; i < not_storted_yet_nbr-1; i++){
            if(project_tab[i].best_befor > project_tab[i+1].best_befor){
                modif = 1;
                tmp_cl = project_tab[i];
                project_tab[i] = project_tab[i+1];
                project_tab[i+1] = tmp_cl;
            }
        }
        not_storted_yet_nbr--;
    }
}