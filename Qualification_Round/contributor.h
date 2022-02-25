#ifndef __CONTRIBUTOR_H__
#define __CONTRIBUTOR_H__
#include "common.h"

#define SKILL_GAP 4

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
int contributor_get_skill_level(int contributor_id, int skill_id);
int *contributor_get_skill_level_ptr(int contributor_id, int skill_id);

int contributor_find_the_best_level_at(int *contributor_ids, int contributor_ids_size, int skill_id);

void contributor_deny_little_skills(struct contributor *contributor);

#endif