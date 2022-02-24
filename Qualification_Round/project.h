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
};



#endif