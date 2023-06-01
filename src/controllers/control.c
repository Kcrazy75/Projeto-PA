#include "control.h"
#include "../models/components.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

App new_app() {
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void*))free_user);
    app->particles = hash_table_create(0,NULL,NULL,NULL,NULL);
    return app;
}

void free_app(App app) {
    hash_table_destroy(app->users);
    free(app);
}

bool has_user(App app, char* name) { return hash_table_get(app->users, name) != NULL; }

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
        if (space != NULL && space->number_of_simulations == 0) { return true; }
    }
    return false;
}

void unregister_user(App app, char* name) { hash_table_remove(app->users, name); }

int equal_names(const void* a, const void* b) {
    User* user_a = (User*)a;
    User* user_b = (User*)b;
    
    return strcmp((*user_a)->name, (*user_b)->name);
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

char* register_particle(App app, char* name, char* space_id,double massa, double carga, int posI[], int v[]){
    Space space = hash_table_get(app->users, name);
    
    char part_id[80];
    sprintf(part_id, "%d", space->next_particle_id);
    space->next_particle_id++;

    Part particle = new_particle(name,massa,carga,posI,v);

    hash_table_insert(space->particles, space_id, particle);
    //hash_table_create(0,NULL,NULL,NULL,free_particle);

    char* part = part_id;
    return part;
}

void change_particle(App app, char* name, char* space_id,double massa, double carga, int posI[], int v[]){
    
    
    //if(cp == 1){ printf("Partícula alterada com sucesso.\n"); }
    //else{ printf("Partícula removida com sucesso.\n"); }
}