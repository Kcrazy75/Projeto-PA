#include "control.h"
#include "../models/components.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

App new_app() {
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void*))free_user);
    return app;
}

void free_app(App app) {
    hash_table_destroy(app->users);
    free(app);
}

bool has_user(App app, char* name) {
    return hash_table_get(app->users, name) != NULL;
}

bool has_space(App app, char* name, char* space_id) {
    User user = hash_table_get(app->users, name);
    return hash_table_get(user->simulation_spaces, space_id) != NULL;
}

void register_user(App app, char* name) {
    User user = new_user(name);
    user->simulation_spaces = hash_table_create(0, NULL, NULL, NULL, (void (*)(void*))free_space);
    user->number_of_simulations = 0;
    hash_table_insert(app->users, name, user);
}

bool check_zero_sim_spaces(App app, char* name) {
    User user = hash_table_get(app->users, name);
    Space space;
    char id[10];
    for (int i = 1; i <= hash_table_size(user->simulation_spaces); i++) {
        sprintf(id, "%d", i);
        space = hash_table_get(user->simulation_spaces, id);
        if (space != NULL && space->number_of_simulations == 0) {
            return true;
        }
    }
    return false;
}

void unregister_user(App app, char* name) {
    hash_table_remove(app->users, name);
}

int equal_names(const void* a, const void* b) {
    User* usera = (User*)a;
    User* userb = (User*)b;
    return strcmp((*usera)->name, (*userb)->name);
}

User* u_list(App app) {
    List list = hash_table_values(app->users);
    User* users = (User*)list_to_array(list);
    qsort(users, list_size(list), sizeof(User), equal_names);
    list_destroy(list, NULL);
    return users;
}

char* register_space(App app, char* user_name) {
    User user = hash_table_get(app->users, user_name);
    char space_id[80];
    sprintf(space_id, "%d", user->next_space_id);
    user->next_space_id++;
    Space space = new_space(space_id);
    space->particles = hash_table_create(0, NULL, NULL, NULL, (void (*)(void*))free_particle);
    space->number_of_simulations = 0;
    hash_table_insert(user->simulation_spaces, space->id, space);
    return space->id;
}

bool check_if_space_exist(App app, char* name, char* space_id) {
    User user = hash_table_get(app->users, name);
    return hash_table_get(user->simulation_spaces, space_id) != NULL;
}

void remove_simulation_space(App app, char* name, char* space_id) {
    User user = hash_table_get(app->users, name);
    Space space = hash_table_remove(user->simulation_spaces, space_id);
    free_space(space);
}

int regist_particle(App app, char* name, char* space_id, char* massa_carga, char* posicao, char* velocidade) {
    User user = hash_table_get(app->users, name);
    Space space = hash_table_get(user->simulation_spaces, space_id);
    Particle particle = (Particle)malloc(sizeof(tParticle));

    char* massa1 = strtok(massa_carga, " ");
    char* carga1 = strtok(NULL, " ");
    int massa = atof(massa1);
    int carga = atoi(carga1);

    particle->massa = massa;
    particle->carga = carga;

    char* pX = strtok(posicao, " ");
    char* pY = strtok(NULL, " ");
    char* pZ = strtok(NULL, " ");

    if (pX == NULL || pY == NULL || pZ == NULL) {
        return 0;

    } else if (massa == 0) {
        return -1;
    }

    particle->posicao[0] = atof(pX);
    particle->posicao[1] = atof(pY);
    particle->posicao[2] = atof(pZ);

    if (strlen(velocidade) == 0) {
        particle->velocidade[0] = 0;
        particle->velocidade[1] = 0;
        particle->velocidade[2] = 0;
    } else {
        char* vX = strtok(velocidade, " ");
        particle->velocidade[0] = atof(vX);
        char* vY = strtok(NULL, " ");
        particle->velocidade[1] = atof(vY);
        char* vZ = strtok(NULL, " ");
        particle->velocidade[2] = atof(vZ);
    }

    char part_id[80];
    space->next_part_id += 1;
    int id = space->next_part_id;  
    sprintf(part_id, "%d", id);                   
    particle->part_id = strdup(part_id);
    hash_table_insert(space->particles, particle->part_id, particle);    return id;
} 