#ifndef __SKILL_H__
#define __SKILL_H__

#include "common.h"

#define MAX_ROLES 1024

int skill_nbr;
int skills_name[MAX_ROLES*MAX_STR*sizeof(char)];

void skill_init();

char *skill_get_name_by_id(int id);

int skill_get_id_otherwise_add(char *skill_str);

#endif