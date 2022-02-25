#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <unistd.h>

#include "common.h"
#include "contributor.h"
#include "project.h"

#include "affectation.h"


//sig_handler
void print_tmp_data(int signum){
    /*
    printf("%d", ingredients_opt_len);
    for(int i = 0; i < ingredients_opt_len; i++){
        printf(" %s", ingredient_get_name_by_id(ingredients_opt[i]));
    }
    printf("\n");
    */
    exit(0);
}


int main(){

    //-----------------------read data--------------------------------
        char str[MAX_STR];
        next_word(str);
        contributor_tab_size = atoi(str);

        next_word(str);
        project_tab_size = atoi(str);

        skill_init();

        contributor_read_data();
        project_read_data();
    //----------------------------------------------------------------

    // fprintf(stderr, "skill_nbr=%d\n", skill_nbr);
    // for(int i = 0; i < skill_nbr; i++){
    //     printf("%s\n",skill_get_name_by_id(i));
    // }
    // fprintf(stderr, "------------------------\n");

    skill_masters_init();

    //fprintf(stderr, "skill %d masters nbr=%d\n", 0, skill_masters_indexes[0]);

    skill_masters_populate();
    skill_masters_reindexetion();

    affectations_init();

    //sig_handler
    signal(SIGINT, print_tmp_data); // Register signal handler
    
    int t = 0;
    while(project_tab_not_handled_yet_nbr>0){
        affectations_update(t++);
    }

    // out
    submition_file();

    skill_masters_free();

    return 0;
}