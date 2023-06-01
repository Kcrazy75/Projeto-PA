#include "cli.h"
#include "../controllers/control.h"
#include "../models/components.h"

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void run_cli() {
    char* line = NULL;
    size_t len = 0;
    App app = new_app();
    while (true) {
        getline(&line, &len, stdin);
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0) {
            break;
        }
        char* command = strtok(line, " ");
        if (strcmp(command, "RJ") == 0) {
            char* name = strtok(NULL, " ");
            if (has_user(app, name)) {
                printf("Utilizador existente.\n");
            } else {
                register_user(app, name);
                printf("Utilizador registado com sucesso.\n");
            }
        } else if (strcmp(command, "EJ") == 0) {
            char* name = strtok(NULL, " ");
            if (!has_user(app, name)) {
                printf("Utilizador inexistente.\n");
            } else if (check_zero_sim_spaces(app, name) == true) {
                printf("Utilizador tem espaços de simulação sem simulações realizadas.\n");
            } else {
                unregister_user(app, name);
                printf("Utilizador removido com sucesso.\n");
            }
        } else if (strcmp(command, "LJ") == 0) {
            if (hash_table_size(app->users) <= 0) {
                printf("Não existem utilizadores registados.\n");

            } else {
                User* users = u_list(app);
                for (int i = 0; i < hash_table_size(app->users); i++) {
                    printf("%s %d %d\n", users[i]->name, hash_table_size(users[i]->simulation_spaces), users[i]->number_of_simulations);
                }
                free(users);
            }
        } else if (strcmp(command, "RE") == 0) {
            char* name = strtok(NULL, " ");
            if (!has_user(app, name)) {
                printf("Utilizador inexistente.\n");
            } else {
                char* space_id = register_space(app, name);
                printf("Espaço de simulação registado com identificador %s.\n", space_id);
            }
        } else if (strcmp(command, "EE") == 0) {
            char* name = strtok(NULL, " ");
            char* space_id = strtok(NULL, " ");
            if (has_user(app, name) == false) {
                printf("Utilizador inexistente.\n");

            } else if (check_if_space_exist(app, name, space_id) == false) {
                printf("Espaço de simulação inexistente.\n");

            } else {
                remove_simulation_space(app, name, space_id);
                printf("Espaço de simulação removido com sucesso.\n");
            }
        } else if (strcmp(command, "RP") == 0) {
            char* name = strtok(NULL, " ");
            char* space_id = strtok(NULL, " ");
            char* massa_carga = NULL;
            size_t space2 = 0;

            getline(&massa_carga, &space2, stdin);
            massa_carga[strlen(massa_carga) - 1] = '\0';
            if (strlen(massa_carga) == 0) {
                free(massa_carga);
                return;
            }

            char* posicao = NULL;
            size_t space3 = 0;

            getline(&posicao, &space3, stdin);
            posicao[strlen(posicao) - 1] = '\0';

            char* velocidade = NULL;
            size_t space4 = 0;

            getline(&velocidade, &space4, stdin);
            velocidade[strlen(velocidade) - 1] = '\0';

            if (has_user(app, name) == false) {
                printf("Utilizador nâo existe.\n");

            } else if (has_space(app, name, space_id) == false) {
                printf("Espaço de simulação inexistente.\n");
            } else {
                int id = regist_particle(app, name, space_id, massa_carga, posicao, velocidade);
                if (id == 0) {
                    printf("Instrução inválida.\n");
                } else if (id == -1) {
                    printf("Massa inválida.\n");
                } else {
                    printf("Partícula registada com identificador %d\n", id);
                }
            }
            free(massa_carga);
            free(posicao);
            free(velocidade);
        } else if (strcmp(command, "AP") == 0) {
        } else if (strcmp(command, "S") == 0) {
        } else {
            printf("Instrução inválida.\n");
        }
        free(line);
        line = NULL;
    }
    if (line != NULL) {
        free(line);
    }
    free_app(app);
}