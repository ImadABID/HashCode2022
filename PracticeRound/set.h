#ifndef __SET_H__
#define __SET_H__

#include "common.h"

int set_l1_nbr;
int *set_l1;

int set_linklist_lent;

struct set *set_linklist;

int max_score;
int ingredients_opt_len;
int *ingredients_opt;

struct set{
    int likes_nbr;
    int hates_nbr;

    int ingredients_nbr;
    int ingredients[MAX_INGR_IN_PIZZA];

    char freez;

    struct set *prev;
};


void set_init();
void set_free();

char update();

#endif