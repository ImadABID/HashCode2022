#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <unistd.h>

#include "common.h"
#include "contributor.h"


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

    char* str[MAX_STR];
    next_word(str);
    contributor_tab_size = atoi(str);

    next_word(str);
    project_tab_size = atoi(str);

    //sig_handler
    signal(SIGINT, print_tmp_data); // Register signal handler

    

    return 0;
}