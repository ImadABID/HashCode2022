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
        contributor_tab[i].available_after = 0;

        for(int j = 0; j< contributor_tab[i].skills_nbre;j++){
            next_word(str);
            contributor_tab[i].skills_id[j] = skill_get_id_otherwise_add(str);
            next_word(str);
            contributor_tab[i].skills_level[j] = atoi(str);
        }

        contributor_deny_little_skills(&(contributor_tab[i]));
    
    }

}

void contributor_deny_little_skills(struct contributor *contributor){
    
    // finding max
    int max_skill_level = 0;
    for(int i = 0; i<contributor->skills_nbre; i++){
        if(contributor->skills_level[i] > max_skill_level){
            max_skill_level = contributor->skills_level[i];
        }
    }

    // computing
    int skills_nbre = 0;
    for(int i = 0; i<contributor->skills_nbre; i++){
        if(max_skill_level - contributor->skills_level[i] < SKILL_GAP){
            skills_nbre++;
        }
    }

    // eliminate
    int *skills_id = malloc(skills_nbre*sizeof(int));
    int *skills_level = malloc(skills_nbre*sizeof(int));

    int j = 0; 
    for(int i = 0; i< contributor->skills_nbre; i++){
        if(max_skill_level - contributor->skills_level[i] < SKILL_GAP){
            skills_id[j] = contributor->skills_id[i];
            skills_level[j] = contributor->skills_level[i];
            j++;
        }
    }

    free(contributor->skills_id);
    free(contributor->skills_level);

    contributor->skills_id = skills_id;
    contributor->skills_level = skills_level;
    contributor->skills_nbre = skills_nbre;
}

char contributor_is_available(int contributor_id, int t){
    return t>=contributor_tab[contributor_id].available_after;
}

int contributor_get_skill_level(int contributor_id, int skill_id){

    struct contributor contr = contributor_tab[contributor_id];

    for(int i = 0; i < contr.skills_nbre; i++){
        if(contr.skills_id[i] == skill_id){
            return contr.skills_level[i];
        }
    }

    return 0;

}

int *contributor_get_skill_level_ptr(int contributor_id, int skill_id){

    struct contributor contr = contributor_tab[contributor_id];

    for(int i = 0; i < contr.skills_nbre; i++){
        if(contr.skills_id[i] == skill_id){
            return &(contr.skills_level[i]);
        }
    }

    return NULL;

}

int contributor_find_the_best_level_at(int *contributor_ids, int contributor_ids_size, int skill_id){
    int max_level = -1;
    int level;

    for(int i = 0; i < contributor_ids_size; i++){
        level = contributor_get_skill_level(contributor_ids[i], skill_id);
        if(level > max_level){
            max_level = level;
        }
    }

    return max_level;
}