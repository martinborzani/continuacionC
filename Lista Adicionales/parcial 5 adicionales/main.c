#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapila.h"

typedef struct nodito{

    float promedio;
    struct nodito *sig;

}NODITO;

typedef NODITO *TLISTA2;

typedef struct nodo{

    char fecha[9];
    TPILA pila;
    struct nodo *sig;

}NODO;

typedef NODO *TLISTA;

void inicializar(TLISTA *lista);
void cargarLista(TLISTA *lista);
void mostrarLista(TLISTA lista);
void mostrarLista2(TLISTA2 lista);
int main()
{
    TLISTA lista,aux;
    TLISTA2 lista2,nuevo,act,ant;
    TELEMENTOP pelem;
    TPILA auxPila;
    int cont,suma;
    float promedio;
    iniciap(&auxPila);
    inicializar(&lista);
    lista2 = NULL;
    cargarLista(&lista);
    aux = lista;
    while(aux != NULL){
        cont = suma = promedio = 0;

        while(!vaciap(aux->pila)){
            cont++;
            sacap(&aux->pila,&pelem);
            suma += pelem;
            ponep(&auxPila,pelem);
        }

        promedio = suma/cont;
        nuevo = (TLISTA2)malloc(sizeof(NODITO));
        nuevo->promedio = promedio;
        nuevo->sig = NULL;
        act = lista2;
        ant = NULL;
        while(act != NULL && promedio > act->promedio){
            ant = act;
            act = act->sig;
        }

        if(lista2 == NULL || promedio < lista2->promedio){
            nuevo->sig = lista2;
            lista2 = nuevo;
        }else{
            ant->sig = nuevo;
            nuevo->sig = act;
        }

        while(!vaciap(auxPila)){

            sacap(&auxPila,&pelem);
            ponep(&aux->pila,pelem);
        }
        aux = aux->sig;
    }


    mostrarLista2(lista2);
    return 0;
}


void inicializar(TLISTA *lista){
    *lista = NULL;
}

void cargarLista(TLISTA *lista){

    TLISTA nuevo,ult;
    TELEMENTOP pelem;
    nuevo = (TLISTA)malloc(sizeof(NODO));
    nuevo->sig = NULL;
    printf("ingrese la fecha\n");
    while(scanf("%s",nuevo->fecha) == 1){
        iniciap(&nuevo->pila);
        if(*lista == NULL){
            *lista = nuevo;
            ult = nuevo;
            printf("ingrese los numeros a la pila\n");
            while(scanf("%d",&pelem) == 1){
                ponep(&nuevo->pila,pelem);
            }

        }else{
            ult->sig = nuevo;
            ult = nuevo;
            printf("ingrese los numeros a la pila\n");
            while(scanf("%d",&pelem) == 1){
                ponep(&nuevo->pila,pelem);
            }
        }

        nuevo = (TLISTA)malloc(sizeof(NODO));
        nuevo->sig = NULL;
        printf("ingrese la fecha\n");
    }


    free(nuevo);
}

void mostrarLista(TLISTA lista){

    TPILA aux;
    TELEMENTOP pelem;
    iniciap(&aux);
    while(lista != NULL){
        printf("%s\n",lista->fecha);
        while(!vaciap(lista->pila)){
            sacap(&lista->pila,&pelem);
            printf("%d\n",pelem);
            ponep(&aux,pelem);
        }

        while(!vaciap(aux)){
            sacap(&aux,&pelem);
            ponep(&lista->pila,pelem);
        }

        lista = lista->sig;
    }

}

void mostrarLista2(TLISTA2 lista){

    while(lista != NULL){
        printf("%.2f\n",lista->promedio);
        lista = lista->sig;
    }
}
