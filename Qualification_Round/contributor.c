#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <unistd.h>

#include "contributor.h"
#include "skill.h"

int contributor_tab_size;
struct contributor* contributor_tab;

void contributor_read_data(){

    char str[MAX_STR];

    contributor_tab = malloc(contributor_tab_size*sizeof(struct contributor));

    for(int i = 0; i< contributor_tab_size; i++){
        
        next_word(str);
        strcpy(contributor_tab[i].contributor_name,str);
        next_word(str);

        contributor_tab[i].skills_nbre = atoi(str);
        contributor_tab[i].skills_id = malloc(contributor_tab[i].skills_nbre*sizeof(int));
        contributor_tab[i].skills_level = malloc(contributor_tab[i].skills_nbre*sizeof(int));

        for(int j = 0; j< contributor_tab[i].skills_nbre;j++){
            next_word(str);
            contributor_tab[i].skills_id[j] = skill_get_id_otherwise_add(str);
            next_word(str);
            contributor_tab[i].skills_level[j] = atoi(str);
        }
    }

}