#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacola.h"
typedef struct nodito{

    char nombreMateria[5];
    struct nodito *sig;

}NODOSUB;

typedef NODOSUB *TSUBLISTA;

typedef struct nodo{

    char matricula[5];
    TSUBLISTA sublista;
    struct nodo *sig;

}NODO;

typedef NODO *TLISTA;

void inicializar(TLISTA *lista);
void cargarLista(TLISTA *lista);
void cargarCola(TCOLA *cola);
void mostrarLista(TLISTA lista);
void mostrarCola(TCOLA cola);

int main()
{
    TLISTA lista,act,ant;
    TSUBLISTA actSub,antSub;
    TCOLA cola;
    TELEMENTOC celem;
    iniciac(&cola);
    inicializar(&lista);
    printf("ingrese dato lista\n");
    cargarLista(&lista);
    printf("ingrese dato cola\n");
    cargarCola(&cola);

    while(!vaciac(cola)){
        sacac(&cola,&celem);
        act = lista;
        ant = NULL;
        while(act != NULL && strcmp(act->matricula,celem.matricula) != 0){
            ant = act;
            act = act->sig;
        }

        if(act != NULL){
            actSub = act->sublista;
            antSub = NULL;
            while(actSub != NULL && strcmp(actSub->nombreMateria,celem.nombreMateria) != 0){
                antSub = actSub;
                actSub = actSub->sig;
            }
            if(actSub != NULL){

                if(antSub == NULL){
                    act->sublista = actSub->sig;
                    free(actSub);
                    actSub = act->sublista;
                }else{
                    antSub->sig = actSub->sig;
                    free(actSub);
                    actSub = antSub->sig;
                }

            }


        }

        if(act->sublista == NULL){
            ant->sig = act->sig;
            free(act);
            act = ant->sig;
        }

    }

    mostrarLista(lista);

    return 0;
}


void inicializar(TLISTA *lista){

    *lista = NULL;
}

void cargarCola(TCOLA *cola){

    TELEMENTOC celem;
    printf("ingrese matricula y final\n");
    while(scanf("%s %s",celem.matricula,celem.nombreMateria) == 2){
        ponec(cola,celem);
        printf("ingrese matricula y final\n");
    }

}

void mostrarCola(TCOLA cola){

    TCOLA aux;
    iniciac(&aux);
    TELEMENTOC celem;
    while(!vaciac(cola)){
        sacac(&cola,&celem);
        printf("%s %s\n",celem.matricula,celem.nombreMateria);
        ponec(&aux,celem);
    }

    while(!vaciac(aux)){
        sacac(&aux,&celem);
        ponec(&cola,celem);
    }
}

void cargarLista(TLISTA *lista){

    TLISTA nuevo,ult;
    TSUBLISTA nuevoSub,ultSub;
    nuevo = (TLISTA)malloc(sizeof(NODO));
    nuevo->sig = NULL;
    printf("ingrese la matricula\n");
    while(scanf("%s",nuevo->matricula) == 1){

        nuevo->sublista = NULL;
        if(*lista == NULL){

            *lista = nuevo;
             ult = nuevo;
             nuevoSub = (TSUBLISTA)malloc(sizeof(NODOSUB));
             nuevoSub->sig = NULL;
            printf("ingrese el codigo de la materia\n");
            while(scanf("%s",nuevoSub->nombreMateria) == 1){
               if(nuevo->sublista == NULL){
                    nuevo->sublista = nuevoSub;
                    ultSub = nuevoSub;
                }else{
                    ultSub->sig = nuevoSub;
                    ultSub = nuevoSub;
                }

                 nuevoSub = (TSUBLISTA)malloc(sizeof(NODOSUB));
                 nuevoSub->sig = NULL;
                 printf("ingrese el codigo de la materia\n");
            }
        }else{

            ult->sig = nuevo;
            ult = nuevo;
            nuevoSub = (TSUBLISTA)malloc(sizeof(NODOSUB));
            nuevoSub->sig = NULL;
            printf("ingrese el codigo de la materia\n");
            while(scanf("%s",nuevoSub->nombreMateria) == 1){
                if(nuevo->sublista == NULL){
                    nuevo->sublista = nuevoSub;
                    ultSub = nuevoSub;
                }else{
                    ultSub->sig = nuevoSub;
                    ultSub = nuevoSub;
                }
                 nuevoSub = (TSUBLISTA)malloc(sizeof(NODOSUB));
                 nuevoSub->sig = NULL;
                 printf("ingrese el codigo de la materia\n");
            }

        }

        nuevo = (TLISTA)malloc(sizeof(NODO));
        nuevo->sig = NULL;
        printf("ingrese la matricula\n");

    }

    free(nuevo);
    free(nuevoSub);

}


void mostrarLista(TLISTA lista){

    TSUBLISTA aux;
    while(lista != NULL){
        aux = lista->sublista;
        printf("%s\n",lista->matricula);
        while(aux != NULL){
            printf("%s\n",aux->nombreMateria);
            aux = aux->sig;
        }

        lista = lista->sig;

    }

}
