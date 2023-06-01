#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "../utils/hash_table.h"
#include "../models/components.h"

typedef struct {
    HashTable users;
} tApp, *App;

App new_app();

void free_app(App app);

bool has_user(App app, char* name);

bool has_space(App app, char* name, char* space_id);

void register_user(App app, char* name);

bool check_zero_sim_spaces(App app, char* name);

void unregister_user(App app, char* name);

int equal_names(const void* a, const void* b);

User* u_list(App app);

char* register_space(App app, char* user_name);

bool check_if_space_exist(App app, char* name, char* space_id);

void remove_simulation_space(App app, char* name, char* space_id);

int regist_particle(App app, char* name, char* space_id, char* massa_carga, char* posicao, char* velocidade);

#endif