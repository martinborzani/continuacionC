#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char codDeporte[6];
    float tiempo;

}Competicion;

typedef struct{

    char codDeporte[6];
    char nombreDeporte[20];
    float tiempo;

}Records;

typedef struct{

    char codDeporte[6];
    int cantidad;

}Porcentaje;


void cargarComp();
void cargarRecords();
void listarArchivo();
void cargarTabla(Records record[], int *n);


int main()
{

    Competicion compe;
    Records reco[20];
    Porcentaje porce[20];
    char deporte[20];
    char maxDeporte[20];
    int n,i,j,cantCompetidores,maxCompetidores,totalCompe;
    cargarTabla(reco,&n);
    float supTiempo,sumTiempo,promedioTiempo,totalPorce;

    FILE *archCompe;

    archCompe = fopen("competicionB.dat","rb");

    if(archCompe != NULL){
        maxCompetidores = 0;
        totalCompe = 0;
        j = 0;
        totalPorce = 0;
        fread(&compe,sizeof(Competicion),1,archCompe);
        printf("Deporte\t\tCant.Competidores\t\tCant.supero el record\tTiempo promedio\n");
        while(!feof(archCompe)){
            i = 0;
            cantCompetidores = 0;
            promedioTiempo = 0;
            supTiempo = 0;
            sumTiempo = 0;
            while(!feof(archCompe) && i < n){

                while(!feof(archCompe) && i < n && strcmp(compe.codDeporte,reco[i].codDeporte) == 0){
                    cantCompetidores++;
                    if(compe.tiempo > reco[i].tiempo){
                        supTiempo++;
                    }
                    sumTiempo += compe.tiempo;
                    strcpy(deporte,compe.codDeporte);
                    fread(&compe,sizeof(Competicion),1,archCompe);
                }// 2do corte

                if(cantCompetidores != 0){
                    i = n; // sale del ciclo si entra al 2do corte
                }
                i++; // suma la variable para encontrar el cod del deporte
            }// 1er corte
            totalCompe += cantCompetidores;
            strcpy(porce[j].codDeporte,deporte);
            porce[j].cantidad = cantCompetidores;
            j++;
            if(cantCompetidores > maxCompetidores){
                maxCompetidores = cantCompetidores;
                strcpy(maxDeporte,deporte);
            }
            promedioTiempo = (float)sumTiempo/cantCompetidores;
            printf("%s\t\t\t%d\t\t\t\t%.2f\t\t\t%.2f \n",deporte,cantCompetidores,supTiempo,promedioTiempo);

        }

        fclose(archCompe);
        printf("Deporte con mayor cantidad de competidores:\t%s \n",maxDeporte);
        printf("Deporte\t\t porcentaje \n");
        for(i = 0; i < j; i++){
            totalPorce = (porce[i].cantidad*100)/totalCompe;
            printf("%s\t\t %.2f \n",porce[i].codDeporte,totalPorce);
            totalPorce = 0;
        }

    }else{
        printf("el archivo no existe \n");
    }



    return 0;
}

void cargarTabla(Records record[], int *n){

    FILE *arch;
    *n = 0;
    arch = fopen("recordsB.dat","rb");
    if(arch != NULL){

        fread(&record[*n],sizeof(Records),1,arch);
        while(!feof(arch)){
            (*n)++;
            fread(&record[*n],sizeof(Records),1,arch);
        }
        fclose(arch);
    }else{
        printf("el archivo no existe");
    }

}


void listarArchivo(){

    Competicion compe;
    Records reco;

    FILE *arch;

    //arch = fopen("recordsB.dat","rb");
    arch = fopen("competicionB.dat","rb");
    if(arch != NULL){
        //fread(&reco,sizeof(Records),1,arch);
        fread(&compe,sizeof(Competicion),1,arch);
        while(!feof(arch)){
           // printf("%s %s %.2f \n",reco.codDeporte,reco.nombreDeporte,reco.tiempo);
           // fread(&reco,sizeof(Records),1,arch);
           printf("%s %.2f \n",compe.codDeporte,compe.tiempo);
           fread(&compe,sizeof(Competicion),1,arch);
        }

        fclose(arch);
    }else{
        printf("el archivo no existe \n");
    }
}


void cargarRecords(){

    Records reco;

    FILE *archT,*archB;

    archT = fopen("Records.txt","r");
    archB = fopen("recordsB.dat","wb");
    if(archT != NULL){

        while(fscanf(archT,"%s %s %f",reco.codDeporte,reco.nombreDeporte,&reco.tiempo) == 3){
            fwrite(&reco,sizeof(Records),1,archB);
        }

        fclose(archB);
        fclose(archT);

    }else{
        printf("el archivo no existe");
    }

}


void cargarComp(){

    Competicion compe;
    FILE *archT,*archB;

    archT = fopen("Competicion.txt","r");
    archB = fopen("competicionB.dat","wb");
    if(archT != NULL){

        while(fscanf(archT,"%s %f",compe.codDeporte,&compe.tiempo) == 2){
            fwrite(&compe,sizeof(Competicion),1,archB);
        }

        fclose(archB);
        fclose(archT);

    }else{
        printf("el archivo no existe");
    }

}
