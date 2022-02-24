#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <unistd.h>

#include "common.h"
#include "contributor.h"
#include "project.h"

#include "affectation.h"

#define T_MAX 100


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
        printf("nobre contribu : %i\n", contributor_tab_size);

        next_word(str);
        project_tab_size = atoi(str);
        printf("nombre project : %i\n", project_tab_size);

        contributor_read_data();
        project_read_data();
    //----------------------------------------------------------------

    for(int i = 0; i< contributor_tab_size; i++){
        for(int j = 0; j< project_tab[i].roles_nbr-1;j++){
            printf("contributor : %s info : %i skills : %i %i\n",contributor_tab[i].contributor_name,contributor_tab[i].skills_nbre,contributor_tab[i].skills_id[j],contributor_tab[i].skills_level[j]);
        }
    }


    for(int i = 0; i< project_tab_size; i++){

        for(int j = 0; j< project_tab[i].roles_nbr;j++){
            printf("project %i : %s info : %i %i %i %i skills : %i %i\n",i+1,project_tab[i].name,project_tab[i].duration,project_tab[i].score,project_tab[i].best_befor,project_tab[i].roles_nbr,project_tab[i].roles_id[j],project_tab[i].roles_level[j]);
        }
    }
    //--------------store by bestfore-------------------------
    project_store_by_bestbefore(project_tab);

    printf("CLASSE NOW BY BESTBEFORE !\n");
    for(int i = 0; i< project_tab_size; i++){
        for(int j = 0; j< project_tab[i].roles_nbr;j++){
            printf("project %i : %s info : %i %i best before : %i %i skills : %i %i\n",i+1,project_tab[i].name,project_tab[i].duration,project_tab[i].score,project_tab[i].best_befor,project_tab[i].roles_nbr,project_tab[i].roles_id[j],project_tab[i].roles_level[j]);
        }
    }


    affectations_init();

    //sig_handler
    signal(SIGINT, print_tmp_data); // Register signal handler
    
    for(int t = 0; t<T_MAX; t++){
        affectations_update(t);
    }

    // out
    

    return 0;
}