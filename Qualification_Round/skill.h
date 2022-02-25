#ifndef __SKILL_H__
#define __SKILL_H__

#include "common.h"

#define MAX_ROLES 10000

int skill_nbr;
char skills_name[MAX_ROLES*MAX_STR*sizeof(char)];

int **skill_masters;
int *skill_masters_indexes;

void skill_init();

char *skill_get_name_by_id(int id);

int skill_get_id_otherwise_add(char *skill_str);

void skill_masters_init();
void skill_masters_free();
void skill_masters_populate();

void skill_masters_store_by_level(int skill_id, int *masters_ids, int masters_ids_size);
void skill_masters_reindexetion();

int skill_masters_get(int skill_id, int skill_level, int *contibutor_id_not_int, int contibutor_id_not_int_size, int t);

void skill_masters_update_rank();

#endif