#include "affectation.h"

void affectations_init(){
    affectations = malloc(project_tab_size * sizeof(struct affectation));
    affectations_size = 0;
}