#ifndef __CONTRIBUTOR_H__
#define __CONTRIBUTOR_H__
#include "common.h"


struct contributor
{
    char contributor_name[MAX_STR];
    int skills_nbre;
    int* skills_id;
    int* skills_level;
};


int contributor_tab_size;
struct contributor* contributor_tab;
#endif