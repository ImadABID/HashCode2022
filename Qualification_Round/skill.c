
#include "skill.h"

void skill_init(){
    skill_nbr = 0;
}

char *skill_get_name_by_id(int id){
    return skills_name+id*MAX_STR;
}

int skill_get_id_otherwise_add(char *skill_str){

    for(int i = 0; i < skill_nbr; i++){
        if(strcmp(skill_str, skill_get_name_by_id(i))==0){
            return i;
        }
    }

    strcpy(skill_get_name_by_id(skill_nbr), skill_str);
    skill_nbr++;

    return skill_nbr-1;

}