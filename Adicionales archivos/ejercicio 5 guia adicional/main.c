#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char fecha[12];
    char codDepo[5];
    float distancia;

}Tiros;

void cargarArchivoBinario();
void leerArchivo();

int main()
{
    Tiros infoTiro;
    FILE *arch;
    char fechaActual[12];
    char codDepoActual[5];
    char fechaMenor[12];
    int totalTiro,depoFecha,menosDepor,n;
    float promDistancia,sumDistancia,minDistancia,promMinimo;


    arch = fopen("tirosB.dat","rb");
    if(arch != NULL){

        promMinimo = 9999;
        menosDepor = 9999;
        fread(&infoTiro,sizeof(Tiros),1,arch);

        while(!feof(arch)){
            depoFecha = 0;
            strcpy(fechaActual,infoTiro.fecha);
            printf("%s\n",infoTiro.fecha);
            printf("Codigo de Deportista\tCantidad de Tiros\tDist.Promedio\tDist.minima\n");
            while(!feof(arch) && strcmp(infoTiro.fecha,fechaActual) == 0){
                strcpy(codDepoActual,infoTiro.codDepo);
                totalTiro  = 0;
                promDistancia = 0;
                sumDistancia = 0;
                minDistancia = infoTiro.distancia;
                printf("%s\t\t\t\t",infoTiro.codDepo);
                while(!feof(arch) && strcmp(infoTiro.fecha,fechaActual) == 0 && strcmp(infoTiro.codDepo,codDepoActual) == 0){
                    totalTiro++;
                    depoFecha++;
                    sumDistancia += infoTiro.distancia;
                    if(infoTiro.distancia < minDistancia){
                        minDistancia = infoTiro.distancia;
                    }
                    fread(&infoTiro,sizeof(Tiros),1,arch);
                }//fin 2do corte

                promDistancia = sumDistancia/totalTiro;
                if(promDistancia < promMinimo){
                    promMinimo = promDistancia;
                }
                printf("%d\t\t\t %.2f\t %.2f\n",totalTiro,promDistancia,minDistancia);


            }// fin 1er corte

            if(depoFecha < menosDepor){
                n = 0;
                menosDepor = depoFecha;
                strcpy(fechaMenor,fechaActual);
            }else if(depoFecha == menosDepor){
                n = 1;
            }



        }// fin de archivo
        printf("El promedio minimo es: %.2f\n",promMinimo);
        if(n){
            printf("Las fechas tienen la misma cantidad de deportistas\n");
        }else{
           printf("la fecha con menor cantidad de deportistas es: %s\n",fechaMenor);
        }
    }else{
        printf("El archivo no existe");
    }

    return 0;
}


void leerArchivo(){

    Tiros infoTiro;
    FILE *arch;

    arch = fopen("tirosB.dat","rb");
    if(arch != NULL){
        fread(&infoTiro,sizeof(Tiros),1,arch);
        while(!feof(arch)){
            printf("%s %s %.2f \n",infoTiro.fecha,infoTiro.codDepo,infoTiro.distancia);
            fread(&infoTiro,sizeof(Tiros),1,arch);
        }

        fclose(arch);
    }else{
        printf("el archivo no existe");
    }

}

void cargarArchivoBinario(){

    Tiros infoTiro;
    FILE *archT,*archB;

    archT = fopen("tiros.txt","r");
    archB = fopen("tirosB.dat","wb");

    if(archT != NULL){
        while(fscanf(archT,"%s %s %f",infoTiro.fecha,infoTiro.codDepo,&infoTiro.distancia) == 3){
            fwrite(&infoTiro,sizeof(Tiros),1,archB);
        }

        fclose(archB);
        fclose(archT);
    }else{

        printf("el archivo no existe");

    }

}
