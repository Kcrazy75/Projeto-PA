#define _POSIX_C_SOURCE 200809L

#include "components.h"

#include <stdlib.h>
#include <string.h>

User new_user(char* name) {
    User user = malloc(sizeof(tUser));
    user->name = strdup(name);
    user->next_space_id = 1;
    user->simulation_spaces = hash_table_create(0, NULL, NULL, NULL, free_space);
    return user;
}

void free_user(User user) {
    free(user->name);
    hash_table_destroy(user->simulation_spaces);
    free(user);
}

Space new_space(char* space_id) {
    Space space = malloc(sizeof(tSpace));
    space->id = strdup(space_id);
    return space;
}

void free_space(void* space) {
    Space s = (Space)space;
    free(s->id);
    free(s);
}

void free_particle(void* particle) {
    Particle p = (Particle)particle;
    free(p->part_id);
    free(p);
}