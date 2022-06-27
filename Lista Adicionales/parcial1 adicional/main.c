#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapila.h"

typedef struct nodito{

    float precio;
    struct nodito *sig;

}NODOSUB;

typedef NODOSUB *TSUBLISTA;

typedef struct nodo{

    float precio;
    char nombre[11];
    TSUBLISTA sublista;
    struct nodo *sig;

}NODO;

typedef NODO *TLISTA;

void inicializar(TLISTA *lista);
void cargarLista(TLISTA *lista);
void mostrarLista(TLISTA lista);
void llenarPila(TLISTA *lista, TPILA pila);
void borrarNodo(TLISTA *lista,char articulo[]);

int main()
{
    TLISTA lista;
    TPILA pila,auxPila;
    TELEMENTOP pelem;
    iniciap(&pila);
    iniciap(&auxPila);
    inicializar(&lista);
    cargarLista(&lista);
    printf("lista original\n");
    mostrarLista(lista);
    llenarPila(&lista,pila);
    printf("lista actualizada\n");
    mostrarLista(lista);
    printf("PILA\n");
    while(!vaciap(pila)){
        sacap(&pila,&pelem);
        printf("%s\n",pelem.articulo);
        ponep(&auxPila,pelem);
    }

    while(!vaciap(auxPila)){
        sacap(&auxPila,&pelem);
        ponep(&pila,pelem);
    }


    return 0;
}

void borrarNodo(TLISTA *lista,char articulo[]){

    TLISTA ant,act;
    act = *lista;
    ant = NULL;
    while(act != NULL && strcmp(articulo,act->nombre) != 0){
        ant = act;
        act = act->sig;
    }
    if(act != NULL){

        ant->sig = act->sig;
        free(act);
        act = ant->sig;

    }else{
        printf("no existe el articulo\n");
    }


}

void llenarPila(TLISTA *lista, TPILA pila){

    TLISTA aux,aux2;
    TSUBLISTA aux3;
    TELEMENTOP pelem;
    int contTotal,contSupera;
    aux = *lista;
    while(aux != NULL){
        aux2 = aux->sig;
        aux3 = aux->sublista;
        contSupera = contTotal = 0;
        while(aux3 != NULL){
            contTotal++;
            if(aux->precio < aux3->precio){
                contSupera++;
            }
            aux3 = aux3->sig;
        }

        if(contTotal == contSupera){
            borrarNodo(lista,aux->nombre);
            strcpy(pelem.articulo,aux->nombre);
            ponep(&pila,pelem);
        }

        aux = aux2;
    }

    free(aux2);
    free(aux);

}


void inicializar(TLISTA *lista){

   *lista = NULL;
}

void cargarLista(TLISTA *lista){

    TLISTA nuevo;
    TSUBLISTA nuevosub;
    nuevo = (TLISTA)malloc(sizeof(NODO));
    nuevo->sig = NULL;
    printf("ingrese articulo y precio\n");
    while(scanf("%s %f",nuevo->nombre,&nuevo->precio) == 2){
        nuevosub = (TSUBLISTA)malloc(sizeof(NODOSUB));
        nuevosub->sig = NULL;
        nuevo->sublista = NULL;
        nuevo->sig = *lista;
        *lista = nuevo;
        fflush(stdin);
        printf("Ingrese los precios actuales\n");
        while(scanf("%f",&nuevosub->precio) == 1){
            nuevosub->sig = nuevo->sublista;
            nuevo->sublista = nuevosub;
            nuevosub = (TSUBLISTA)malloc(sizeof(NODOSUB));
            nuevosub->sig = NULL;
            printf("Ingrese los precios actuales\n");
        }
        nuevo = (TLISTA)malloc(sizeof(NODO));
        nuevo->sig = NULL;
        printf("ingrese articulo y precio\n");
    }

    free(nuevo);
    free(nuevosub);
}

void mostrarLista(TLISTA lista){

    TSUBLISTA aux;
    while(lista != NULL){
        aux = lista->sublista;
        printf("%s %.2f\n",lista->nombre,lista->precio);
        while(aux != NULL){
            printf("%.2f\n",aux->precio);
            aux = aux->sig;
        }
        lista = lista->sig;
    }

}
