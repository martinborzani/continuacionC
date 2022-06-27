#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char codEspe[4];
    float tonelada;

}Especie;

typedef struct{

    char codEmpresa[5];
    Especie cupos[20];

}Cupos;

typedef struct{

    char codEmpresa[5];
    char codBarco[4];
    Especie captura[20];

}Capturas;


void cargarCuposB();
void cargarCapturasB();
void mostrarArchivo();

int main()
{
   // cargarCuposB();
    mostrarArchivo();

    return 0;
}

void mostrarArchivo(){

    Cupos cup;
    FILE *arch;
    int i;
    arch = fopen("CuposB.dat","rb");
    if(arch != NULL){
        i = 0;
        fread(&cup,sizeof(Cupos),1,arch);
        while(!feof(arch)){
            printf("%s %s %.2f \n",cup.codEmpresa,cup.cupos[i].codEspe,cup.cupos[i].tonelada);
            i++;
            fread(&cup,sizeof(Cupos),1,arch);
        }

        fclose(arch);

    }else{
        printf("el archivo no existe");
    }

}

void cargarCuposB(){

    Cupos cup;
    FILE *archT, *archB;
    int i;

    archT = fopen("Cupos.txt","r");
    archB = fopen("CuposB.dat","wb");

    if(archT != NULL){
        i = 0;
        while(fscanf(archT,"%s %s %f",cup.codEmpresa,cup.cupos[i].codEspe,&cup.cupos[i].tonelada) == 3){
            fwrite(&cup,sizeof(Cupos),1,archB);
            i++;
        }

        fclose(archB);
        fclose(archT);

    }else{
        printf("el archivo no existe");
    }

}


