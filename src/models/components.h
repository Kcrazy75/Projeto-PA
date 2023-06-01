#ifndef MODELS_H
#define MODELS_H

#include "../utils/hash_table.h"

typedef struct {
    char* name;
    HashTable simulation_spaces;
    int next_space_id;
    int number_of_simulations;
} tUser, *User;

typedef struct {
    char* id;
    HashTable particles;
    int next_particle_id;
    int number_of_simulations;
} tSpace, *Space;

typedef struct {
    char* name;
    double massa;
    double carga;
    int coord[3];
    int v[3];
} tPart, *Part;

User new_user(char* name);

void free_user(User user);

Space new_space(char* space_id);

void free_space(void* space);

Part new_particle(char* name, double massa, double carga, int posI[], int v[]);

void free_particle(Part particle);

#endif