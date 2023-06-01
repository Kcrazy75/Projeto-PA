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

        if (strlen(line) == 0) { break; }

        char* command = strtok(line, " ");
        
        if (strcmp(command, "RJ") == 0) {
            char* name = strtok(NULL, " ");
            if(name == NULL){ printf("Instrução inválida.\n"); }
            else if (has_user(app, name)) {
                    printf("Utilizador existente.\n");
            } else {
                register_user(app, name);
                printf("Utilizador registado com sucesso.\n");
            }
        } else if (strcmp(command, "EJ") == 0) {
            char* name = strtok(NULL, " ");
            if(name == NULL){ printf("Instrução inválida.\n"); }
            else if (!has_user(app, name)) {
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

            if(name == NULL){ printf("Instrução inválida.\n"); }
            else if (!has_user(app, name)){
                printf("Utilizador inexistente.\n");
            } else {
                char* space_id = register_space(app, name);
                printf("Espaço de simulação registado com identificador %s.\n", space_id);
            }
        } else if (strcmp(command, "EE") == 0) {
            char* name = strtok(NULL, " ");
            char* space_id = strtok(NULL, " ");

            if(name == NULL || space_id == NULL){ printf("Instrução inválida.\n"); }
            else if (has_user(app, name) == false) {
                printf("Utilizador inexistente.\n");
            } else if (check_if_space_exist(app, name, space_id) == false) {
                printf("Espaço de simulação inexistente.\n");
            } else {
                remove_simulation_space(app, name, space_id);
                printf("Espaço de simulação removido com sucesso.\n");
            }
        } else if (strcmp(command, "RP") == 0) {
            char* name = strtok(NULL, " ");
            char* space_id = strtok(NULL," ");

            //Seg-Fault fix
            if(name == NULL || space_id == NULL){ printf("Instrução inválida.\n"); }
            else{
                //Linha 2
                char* line2 = NULL;
                len = 0;
                    
                getline(&line2,&len,stdin);
                line2[strlen(line2) - 1] = '\0';

                char* string = strtok(line2," ");
                double massa = atof(string);
                string = strtok(NULL, " ");
                double carga = atof(string);
                
                //Linha 3
                char* line3 = NULL;
                len = 0;
                    
                getline(&line3,&len,stdin);
                line3[strlen(line3) - 1] = '\0';

                int piX = atoi(strtok(line3, " "));
                int piY = atoi(strtok(NULL, " "));
                int piZ = atoi(strtok(NULL, " "));

                //Linha 4
                char* line4 = NULL;
                len = 0;
                    
                getline(&line4,&len,stdin);
                line4[strlen(line4) - 1] = '\0';

                int vX = atoi(strtok(line4, " "));
                int vY = atoi(strtok(NULL, " "));
                int vZ = atoi(strtok(NULL, " "));
            
                if (!has_user(app, name)) { 
                printf("Utilizador inexistente.\n");
                } else {
                    if (check_if_space_exist(app,name,space_id)) {
                        if(massa > 0){
                            int posI[3] = {piX,piY,piZ};
                            int v[3] = {vX,vY,vZ};
                        
                            char* part_id = register_particle(app,name,space_id,massa,carga,posI,v);
                            printf("%s%s%s","Partícula registada com identificador ",part_id,".\n");
                        } else { printf("Massa inválida.\n"); }
                    } else { printf("Espaço de simulação inexistente.\n"); }
                }
            }
        } else if (strcmp(command, "AP") == 0) {
            char* name = strtok(NULL, " ");
            char* space_id = strtok(NULL," ");

            //Seg-Fault fix
            if(name == NULL || space_id == NULL){ printf("Instrução inválida.\n"); }
            else{
                //Linha 2
                char* line2 = NULL;
                len = 0;
                    
                getline(&line2,&len,stdin);
                line2[strlen(line2) - 1] = '\0';

                char* string = strtok(line2," ");
                double massa = atof(string);
                string = strtok(NULL, " ");
                double carga = atof(string);
                
                //Linha 3
                char* line3 = NULL;
                len = 0;
                    
                getline(&line3,&len,stdin);
                line3[strlen(line3) - 1] = '\0';

                int piX = atoi(strtok(line3, " "));
                int piY = atoi(strtok(NULL, " "));
                int piZ = atoi(strtok(NULL, " "));

                //Linha 4
                char* line4 = NULL;
                len = 0;
                    
                getline(&line4,&len,stdin);
                line4[strlen(line4) - 1] = '\0';

                int vX = atoi(strtok(line4, " "));
                int vY = atoi(strtok(NULL, " "));
                int vZ = atoi(strtok(NULL, " "));
            
                if (!has_user(app, name)) { 
                printf("Utilizador inexistente.\n");
                } else {
                    if (check_if_space_exist(app,name,space_id)) {
                        if(/*particula existe ou nao*/true){
                            if(massa > 0){      //validar massa
                                int posI[3] = {piX,piY,piZ};
                                int v[3] = {vX,vY,vZ};
                                change_particle(app,name,space_id,massa,carga,posI,v);
                                //if(cp == 1){ printf("Partícula alterada com sucesso.\n"); }
                                //else{ printf("Partícula removida com sucesso.\n"); }
                            }
                        } else { printf("Massa inválida.\n"); } //remove se PO nao existe
                    } else { printf("Espaço de simulação inexistente.\n"); }
                }
            }
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