#ifndef __CONTRIBUTOR_H__
#define __CONTRIBUTOR_H__
#include "common.h"


struct contributor
{
    char contributor_name[MAX_STR];
    int skills_nbre;
    int* skills_id;
    int* skills_level;

    int available_after;

};

int contributor_tab_size;
struct contributor* contributor_tab;

//read data
void contributor_read_data();
char contributor_is_available(int contributor_id, int t);

#endif