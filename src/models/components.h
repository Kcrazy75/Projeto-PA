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
    int number_of_simulations;
    int next_part_id;
    HashTable particles;
    // TODO: Mais coisas
} tSpace, *Space;

typedef struct {  
    double carga;
    double massa;
    double posicao[3];  
    double velocidade[3];
    double aceleracao[3];
    char* part_id;
} tParticle, *Particle;

User new_user(char* name);

void free_user(User user);

Space new_space(char* space_id);

void free_space(void* space);

void free_particle(void* particle);

#endif