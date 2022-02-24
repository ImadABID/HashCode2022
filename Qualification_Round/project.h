#ifndef __PROJECT_H__
#define __PROJECT_H__

#include "common.h"

struct project{
    char name[MAX_STR];
    int duration;
    int best_befor;
    int score;

    int roles_nbr;
    int *roles_id;
    int *roles_level;

    char affected;

};

//read data
void project_read_data();

//store by best befor
void project_store_by_bestbefore(struct  project* project_tab);


int project_tab_size;
struct  project* project_tab;

#endif