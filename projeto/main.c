
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "utils/src/list.h"
#include "utils/src/hash_table.h"

typedef struct{
    HashTable users;
    char* nome[120];
}tUser,*User;

typedef struct{
    char* nome[120];
    
    char tipo;
    double massa;
    double carga;
    int cord[3];
    float velo;
    float acel;
    float fGrav;
    float fElec;
    float fTotal;
}tPart,*Part;

typedef struct{
    User users;
    Part particulas;

    int indx;
    float intervaloTempo;
    float tMax;
}tCampo,*Campo;

int hash(HashTable users, char* nome){
    int hash = 0;
    int a = 120;
    int size = hash_table_size(users);
    for (size_t i = 0; i < strlen(nome); i++) {
        hash = (hash * a + nome[i]) % size;
    }
    return hash;
}

void registarUtilizador(HashTable users, char* nome){
    User user = malloc(sizeof(tUser));
    strcpy(user->nome, nome);
    int key = hash(users, nome);
    
    user->users = hash_table_create(0,hash,NULL,NULL,NULL);
    hash_table_insert(users, (int) key, user);
}

int user_exists(HashTable users, char* nome){
    if(hash_table_get(users,nome) == NULL){ return 1; }
    else{ return 0; }
}

void removerUtilizador(HashTable users, char* nome){
   //remover
}

void listarUtilizadores(HashTable users){
    //listar utilizadores
}

void registarEspaco(HashTable users, int i, char* nome){
    //criar
}

bool verificarEspaco(char* nome, int i){
    //verificar
}

void removerEspaco(char* nome, int i){
    //remover
}

bool verificarUser(HashTable users, char* name){
    return true;
}

void free_users(void* u){
    User user = (User) u;
    hash_table_destroy(user->users);
    free(user); 
}

int main(){
    int iE = 1;
    char* line = NULL;
    size_t len = 0;

    HashTable users = hash_table_create(0, NULL, NULL, NULL, NULL);

    while(true){
        getline(&line,&len,stdin);
        line[strlen(line)-1] = '\0';

        if(strlen(line) == 0){ break; }

        char* commando = strtok(line," ");

        if(strcmp(commando,"RJ") == 0){
            char* name = strtok(NULL," ");

            //HashTable users = hash_table_create(0, NULL, NULL, NULL, NULL);

            if(user_exists(users, name)){ printf("Utilizador existente.\n"); }
            else{
                registarUtilizador(users, name);
                printf("Utilizador registado com sucesso.\n");
            }
        }
        else if(strcmp(commando,"EJ") == 0){
            char* name = strtok(NULL," ");

            if(user_exists(users, name)){
                if(verificarUser(users, name)){
                    printf(" Utilizador tem espaços de simulação sem simulações realizadas.\n");
                }
                else { 
                    removerUtilizador(users, name);
                    printf("Utilizador removido com sucesso.\n");
                }
            }
            else{
                printf("Utilizador não existente.\n");
            }
        }
        else if(strcmp(commando,"LJ") == 0){
            if(hash_table_is_empty){ printf("Não existem utilizadores registados.\n"); }
            else{ listarUtilizadores(users); }
        }else if(strcmp(commando,"RE") == 0){
            char* name = strtok(NULL," ");

            if(user_exists(users, name)){ 
                registarEspaco(users,iE,name);
                 printf("%s%d%s, Espaço de simulação registado com identificador ", iE, " . \n");
            }
            else { printf("Utilizador inexistente. \n"); }
        }else if(strcmp(commando,"EE") == 0){
            char* name = strtok(NULL," ");
            int iE = atoi(strtok(NULL," "));

            if(user_exists(users,name)){
                if(verificarEspaco(name,iE)){
                    removerEspaco(name,iE);
                    printf(" Espaço de simulação removido com sucesso.\n");
                }
                else { printf("Espaço de simulação inexistente. \n"); }
            }
            else{ printf("Utilizador inexistente. \n"); }
        }else if(strcmp(commando,"RP") == 0){
            
        }else if(strcmp(commando,"AP") == 0){
            
        }else if(strcmp(commando,"S") == 0){
            
        }
        else { printf("instrucao invalida!\n"); }

        free(line);
        line = NULL;
    }
    if(line != NULL){ free(line); }
    free_users(users);

    return 0;
}