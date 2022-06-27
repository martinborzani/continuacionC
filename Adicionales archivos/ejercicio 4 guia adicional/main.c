#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char proyecto[5];
    int empleado;
    int NumSemana;
    int horasLaboral;

}HoraSemanal;

typedef struct{

    char proyecto[5];
    int horaEstimada;

}HoraProy;


void cargarHoraSemanal();
void cargarHoraProy();
void leerArchivos();
void cargarTabla(HoraProy proy[], int *n);
int obtenerIndice(HoraProy proy[],char codProye[] ,int n);


int main()
{

    HoraProy proy[10];
    HoraSemanal hrSema;
    int i,n,pos,maxEmple,maxHoras,contHoras;
    float desvio;
    char proyActual[5];
    FILE *archSemana;
    cargarTabla(proy,&n);

    archSemana = fopen("HoraSemanalB.dat","rb");
    if(archSemana != NULL){

        fread(&hrSema,sizeof(HoraSemanal),1,archSemana);
        while(!feof(archSemana)){
            pos = obtenerIndice(proy,hrSema.proyecto,n);
            maxEmple = hrSema.empleado;
            maxHoras = hrSema.horasLaboral;
            contHoras = 0;
            strcpy(proyActual,hrSema.proyecto);
            printf("Proyecto: %s\n",proy[pos].proyecto);
            while(!feof(archSemana) && strcmp(hrSema.proyecto,proyActual) == 0){
                printf("%d\t\t%d\n",hrSema.empleado,hrSema.horasLaboral);
                if(maxHoras < hrSema.horasLaboral){
                    maxEmple = hrSema.empleado;
                    maxHoras = hrSema.horasLaboral;
                }
                contHoras += hrSema.horasLaboral;
                fread(&hrSema,sizeof(HoraSemanal),1,archSemana);
            }

            desvio =  ((contHoras - proy[pos].horaEstimada) / proy[pos].horaEstimada)*100;
            printf("Empleado con mas horas trabajadas en el proy: %d con %d hs\n",maxEmple,maxHoras);
            printf("Horas Proyecto %s: %d . %d estimadas. Desvio: %.2f \n",proy[pos].proyecto,contHoras,proy[pos].horaEstimada,desvio);
        }

    }else{
        printf("el archivo no existe");
    }




    return 0;
}


int obtenerIndice(HoraProy proy[],char codProye[] ,int n){

    int i;
    i = 0;
    while(i < n && strcmp(proy[i].proyecto,codProye)){
        i++;
    }

    return i;


}

void cargarTabla(HoraProy proy[],int *n){


    FILE *arch;
    *n = 0;
    arch = fopen("HoraProyectoB.dat","rb");
    if(arch != NULL){

        fread(&proy[*n],sizeof(HoraProy),1,arch);
        while(!feof(arch)){
            (*n)++;
            fread(&proy[*n],sizeof(HoraProy),1,arch);
        }

        fclose(arch);

    }else{
        printf("el archivo no existe");
    }


}

void leerArchivos(){

    HoraProy proy;
    HoraSemanal hrSema;
    FILE *arch;
    //arch = fopen("HoraSemanalB.dat","rb");
    arch = fopen("HoraProyectoB.dat","rb");
    if(arch != NULL){

        //fread(&hrSema,sizeof(HoraSemanal),1,arch);
        fread(&proy,sizeof(HoraProy),1,arch);
        while(!feof(arch)){
            //printf("%s %d %d %d\n",hrSema.proyecto,hrSema.empleado,hrSema.NumSemana,hrSema.horasLaboral);
            //fread(&hrSema,sizeof(HoraSemanal),1,arch);
            printf("%s %d \n",proy.proyecto,proy.horaEstimada);
            fread(&proy,sizeof(HoraProy),1,arch);
        }

        fclose(arch);

    }else{
        printf("el archivo no existe");
    }

}

void cargarHoraSemanal(){

    HoraSemanal hrSema;
    FILE *archT,*archB;

    archT = fopen("HoraSemanal.txt","r");
    archB = fopen("HoraSemanalB.dat","wb");

    if(archT != NULL){

        while(fscanf(archT,"%s %d %d %d",hrSema.proyecto,&hrSema.empleado,&hrSema.NumSemana,&hrSema.horasLaboral) == 4){
            fwrite(&hrSema,sizeof(HoraSemanal),1,archB);
        }

        fclose(archB);
        fclose(archT);

    }else{
        printf("el archivo no existe");
    }

}

void cargarHoraProy(){

    HoraProy proye;
    FILE *archT,*archB;

    archT = fopen("HoraProyecto.txt","r");
    archB = fopen("HoraProyectoB.dat","wb");

    if(archT != NULL){

        while(fscanf(archT,"%s %d",proye.proyecto,&proye.horaEstimada) == 2){
            fwrite(&proye,sizeof(HoraProy),1,archB);
        }

        fclose(archB);
        fclose(archT);

    }else{
        printf("el archivo no existe");
    }

}
