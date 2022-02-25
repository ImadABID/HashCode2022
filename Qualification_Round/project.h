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
    char skipped;

};

//read data
void project_read_data();

//store by best befor
void project_store_by_bestbefore(struct  project* project_tab);

char project_start_time_has_past(int project_id, int t);

int project_tab_size;
struct  project* project_tab;

int project_tab_not_handled_yet_nbr;

#endif