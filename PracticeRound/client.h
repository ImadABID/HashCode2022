#ifndef __CLEINT_H__
#define __CLEINT_H__

#include "common.h"

int clients_nbr;
struct client *clients;

struct client{
    int likes_nbr;
    int *likes;
    int hates_nbr;
    int *hates;
};

void clients_init_and_read_data();
void clients_free();


char client_likes_ingredient(struct client client, int ingredient_id);
char client_hates_ingredient(struct client client, int ingredient_id);
char client_accept(struct client client, int *ingredient_ids, int ingredient_ids_size);
char client_accept_now(struct client client, int *ingredient_ids, int ingredient_ids_size);

#endif