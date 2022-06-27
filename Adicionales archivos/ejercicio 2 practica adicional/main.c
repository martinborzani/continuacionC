#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{

    char fecha[12];
    int lejago;
    char hrTeorico[6];
    char hrReal[6];
    char estado;

} HoraPersonal;

typedef struct
{

    char fecha[12];
    int legajo;
    char hora[6];

} Entrada;


void cargarHoraPersonal();
void cargarEntrada();
void leerArchivo();


int main()
{

    HoraPersonal hrPerso;
    Entrada entradas;
    int totalT,contAus,contEmp,contError;


    FILE *archHrPerso, *archEntrada, *archNuevo;

    archEntrada = fopen("relojEntradaB.dat","rb");
    archHrPerso = fopen("horaPersonalB.dat","rb");
    cargarEntrada();
    if(archEntrada != NULL || archHrPerso != NULL)
    {

        archNuevo = fopen("archivoActual.dat","wb");
        fread(&hrPerso,sizeof(HoraPersonal),1,archHrPerso);
        fread(&entradas,sizeof(Entrada),1,archEntrada);
        totalT = 0;
        contAus = 0;
        contEmp = 0;
        contError = 0;
        while(!feof(archHrPerso) || !feof(archEntrada))
        {
            if(strcmp(hrPerso.fecha,entradas.fecha) == 0 && hrPerso.lejago == entradas.legajo)
            {
                strcpy(hrPerso.hrReal,entradas.hora);
                if(strcmp(hrPerso.hrTeorico,hrPerso.hrReal)<0)
                {
                    hrPerso.estado = 'T';
                    totalT++;
                    contEmp++;
                }
                else
                {
                    hrPerso.estado = 'P';
                    contEmp++;
                }

                if(strcmp(hrPerso.fecha,"ZZZZZZZZ") == 0){

                    fread(&hrPerso,sizeof(HoraPersonal),1,archHrPerso);
                    fread(&entradas,sizeof(Entrada),1,archEntrada);
                }else{
                    fwrite(&hrPerso,sizeof(HoraPersonal),1,archNuevo);
                    fread(&hrPerso,sizeof(HoraPersonal),1,archHrPerso);
                    fread(&entradas,sizeof(Entrada),1,archEntrada);
                }




            }
            else if(strcmp(hrPerso.fecha,entradas.fecha) == 0 && hrPerso.lejago < entradas.legajo)
            {

                hrPerso.estado = 'A';
                contAus++;
                contEmp++;
                fwrite(&hrPerso,sizeof(HoraPersonal),1,archNuevo);
                fread(&hrPerso,sizeof(HoraPersonal),1,archHrPerso);

            }
            else
            {
                contError++;
                fread(&entradas,sizeof(Entrada),1,archEntrada);
                if(strcmp(entradas.fecha,"ZZZZZZZZ") == 0){
                    hrPerso.estado = 'A';
                    contAus++;
                    fwrite(&hrPerso,sizeof(HoraPersonal),1,archNuevo);
                    fread(&hrPerso,sizeof(HoraPersonal),1,archHrPerso);
                }
            }

        }

        fclose(archEntrada);
        fclose(archHrPerso);
        fclose(archNuevo);

    }
    else
    {
        printf("el archivo no existe");
    }

    leerArchivo();
    printf("%.2f de ausentimos \n",(float)contAus*100/contEmp);
    printf("%d entradas demoradas \n",totalT);
    printf("%d fichadas erroneas",contError - 1);


    return 0;
}


void leerArchivo()
{

    HoraPersonal hrPerso;
    Entrada entrada;
    FILE *arch;

    //arch = fopen("horaPersonalB.dat","rb");
    //arch = fopen("relojEntradaB.dat","rb");
    arch = fopen("archivoActual.dat","rb");
    if(arch != NULL)
    {

        fread(&hrPerso,sizeof(HoraPersonal),1,arch);
        //fread(&entrada,sizeof(Entrada),1,arch);

        while(!feof(arch))
        {
            printf("%s %d %s %s %c\n",hrPerso.fecha,hrPerso.lejago,hrPerso.hrTeorico,hrPerso.hrReal,hrPerso.estado);
            fread(&hrPerso,sizeof(HoraPersonal),1,arch);
            // printf("%s %d %s\n",entrada.fecha,entrada.legajo,entrada.hora);
            // fread(&entrada,sizeof(Entrada),1,arch);
        }

        fclose(arch);

    }
    else
    {
        printf("el archivo no existe");
    }



}

void cargarHoraPersonal()
{

    HoraPersonal hrPerso;
    FILE *archT, *archB;

    archT = fopen("HoraEntPersonal.txt","r");
    archB = fopen("horaPersonalB.dat","wb");

    if(archT != NULL)
    {

        while(fscanf(archT,"%s %d %s %s %c",hrPerso.fecha,&hrPerso.lejago,hrPerso.hrTeorico,hrPerso.hrReal,&hrPerso.estado) == 5)
        {
            fwrite(&hrPerso,sizeof(HoraPersonal),1,archB);
        }

        fclose(archB);
        fclose(archT);

    }
    else
    {
        printf("el archivo no existe");
    }

}

void cargarEntrada()
{

    Entrada entradas;
    FILE *archT, *archB;

    archT = fopen("RelojEntrada.txt","r");
    archB = fopen("relojEntradaB.dat","wb");

    if(archT != NULL)
    {

        while(fscanf(archT,"%s %d %s",entradas.fecha,&entradas.legajo,entradas.hora) == 3)
        {
            fwrite(&entradas,sizeof(Entrada),1,archB);
        }

        fclose(archB);
        fclose(archT);

    }
    else
    {
        printf("el archivo no existe");
    }

}
