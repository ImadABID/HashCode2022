#ifndef __INGREDIENT_H__
#define __INGREDIENT_H__

#include "common.h"

int ingredient_max_nbr; // init at ingredient_init()
int ingredient_nbr;

char *ingredient_names;

void ingredient_init(int nbr_clients);
void ingredient_free();

char *ingredient_get_name_by_id(int id);
int ingredient_get_id_otherwise_add(char *ingredient_str);

void ingredient_likes_hates(int *likes_nbr, int *hates_nbr, int ingredient_id);
void ingredient_likes_hates_for_set(int *likes_nbr, int *hates_nbr, int *ingredient_ids, int ingredient_ids_size);

int ingredient_set_score(int *ingredient_ids, int ingredient_ids_size);

#endif