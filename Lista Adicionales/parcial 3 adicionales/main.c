#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapila.h"

typedef struct nodo{

    char nombre[15];
    TPILA pila;
    struct nodo *sig;

}NODO;

typedef NODO *TLISTA;

void inicializar(TLISTA *lista);
void cargarLista(TLISTA *lista);
void mostrarLista(TLISTA lista);
void eliminar(TLISTA *lista,char nombre[]);

int main()
{
    TLISTA lista,aux,ant,auxAUX;;
    TPILA auxPila;
    TELEMENTOP pelem;
    char paloAux;
    int cont,contIguales,centinela;
    inicializar(&lista);
    iniciap(&auxPila);
    cargarLista(&lista);
    aux = lista;
    centinela = 0;
    while(aux != NULL){
        auxAUX = aux->sig;
        cont = contIguales = 0;
        consultap(aux->pila,&pelem);
        paloAux = pelem.palo;
        while(!vaciap(aux->pila)){
            cont++;
            sacap(&aux->pila,&pelem);
            if(paloAux == pelem.palo){
                contIguales++;
            }
            ponep(&auxPila,pelem);
        }

        while(!vaciap(auxPila)){
            sacap(&auxPila,&pelem);
            ponep(&aux->pila,pelem);
        }

        if(cont == contIguales){

            printf("llegue\n");
            eliminar(&lista,aux->nombre);
            aux = auxAUX;

        }else{
            aux = auxAUX;
           // centinela = 1;
        }

    }

    mostrarLista(lista);


    return 0;
}

void inicializar(TLISTA *lista){

    *lista = NULL;
}

void eliminar(TLISTA *lista,char nombre[]){

    TLISTA act,ant;
    act = *lista;
    ant = NULL;
    while(act != NULL && strcmp(nombre,act->nombre) != 0){
        ant = act;
        act = act->sig;
    }

    if(ant == NULL){
        *lista = act->sig;
        free(act);
        act = *lista;
    }else{
        ant->sig = act->sig;
        free(act);
        act = ant->sig;
    }

}

void cargarLista(TLISTA *lista){

    TLISTA nuevo,ult;
    TELEMENTOP pelem;
    nuevo = (TLISTA)malloc(sizeof(NODO));
    nuevo->sig = NULL;
    printf("ingrese nombre del jugador \n");
    while(scanf("%s",nuevo->nombre) == 1){

        if(*lista == NULL){
            *lista = nuevo;
            ult = nuevo;
            iniciap(&nuevo->pila);
            printf("ingrese numero de carta y palo\n");
            while(scanf("%d %c",&pelem.num,&pelem.palo) == 2){
                ponep(&nuevo->pila,pelem);
            }
        }else{
            ult->sig = nuevo;
            ult = nuevo;
            iniciap(&nuevo->pila);
            printf("ingrese numero de carta y palo\n");
            while(scanf("%d %c",&pelem.num,&pelem.palo) == 2){
                ponep(&nuevo->pila,pelem);
            }

        }

         nuevo = (TLISTA)malloc(sizeof(NODO));
        nuevo->sig = NULL;
        printf("ingrese nombre del jugador \n");

    }

    free(nuevo);
}

void mostrarLista(TLISTA lista){

    TPILA aux;
    TELEMENTOP pelem;
    iniciap(&aux);
    while(lista != NULL){
        printf("jugadora: %s \n",lista->nombre);
        printf("cartas\n");
        while(!vaciap(lista->pila)){
            sacap(&lista->pila,&pelem);
            printf("%d %c\n",pelem.num,pelem.palo);
            ponep(&aux,pelem);
        }

        while(!vaciap(lista->pila)){
            sacap(&lista->pila,&pelem);
            printf("%d %c\n",pelem.num,pelem.palo);
            ponep(&aux,pelem);
        }
        lista = lista->sig;
    }

}
