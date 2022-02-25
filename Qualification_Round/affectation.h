#ifndef __AFFECTATION_H__
#define __AFFECTATION_H__

#include "common.h"

#include "project.h"
#include "skill.h"

struct affectation{
    int project_id;

    int contributor_ids_size; // project nbr_roles
    int *contributor_ids;
};

int affectations_size ;
struct affectation *affectations;

void affectations_init();
void affectations_update(int t);
void submition_file();

#endif