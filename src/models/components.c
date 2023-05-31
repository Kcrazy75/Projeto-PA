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

Part new_particule(char* name, char* part_id, double massa, double carga, int posI[], int v[]){
    Part particule = malloc(sizeof(tPart));

    particule->name = strdup(name);
    particule->massa = massa;
    particule->carga = carga;
    
    for(int a = 0;a < 3;a++){
        particule->coord[a] = posI[a];
        particule->v[a] = v[a];
    }

    return particule;
}

void free_particule(Part part){
    free(part->name);
    //free(part->carga);
}