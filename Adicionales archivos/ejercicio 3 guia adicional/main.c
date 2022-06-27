#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char NroInsc[5];
    char apellido[20];
    int cantInasis;

}Inscriptos;

typedef struct{

    char NroInsc[5];
    char apellido[20];

}Asistencia;

void cargarInscriptos();
void cargarAsistencias();
void listarArchivo();

int main()
{

   Asistencia asis;
   Inscriptos insc;
   char vecNoInscr[20][20];
   int totalAsistecia,i,n,cantAsistentes;
   float porcAusentismo;

   FILE *archAsis, *archInsc, *archActual;

   archAsis = fopen("asistenciaB.dat","rb");
   archInsc = fopen("inscriptosB.dat","rb");
   archActual = fopen("actualB.dat","wb");

   if(archInsc != NULL || archAsis != NULL){

    printf("Ingrese el total de clases \n");
    scanf("%d",&totalAsistecia);
    i = 0;
    cantAsistentes = 0;
    fread(&asis,sizeof(Asistencia),1,archAsis);
    fread(&insc,sizeof(Inscriptos),1,archInsc);
    while(!feof(archAsis) || !feof(archInsc)){
        porcAusentismo = 0;
        if(strcmp(insc.NroInsc,asis.NroInsc)<0){
            insc.cantInasis++;
            porcAusentismo = (insc.cantInasis*100)/totalAsistecia;
            if(porcAusentismo >= 30){
               fread(&insc,sizeof(Inscriptos),1,archInsc);
            }else{
               fwrite(&insc,sizeof(Inscriptos),1,archActual);
               fread(&insc,sizeof(Inscriptos),1,archInsc);
            }

        }else if(strcmp(insc.NroInsc,asis.NroInsc)>0){
                 strcpy(vecNoInscr[i],asis.apellido);
                 i++;
                 fread(&asis,sizeof(Asistencia),1,archAsis);
              }else{
                cantAsistentes++;
                fwrite(&insc,sizeof(Inscriptos),1,archActual);
                fread(&insc,sizeof(Inscriptos),1,archInsc);
                fread(&asis,sizeof(Asistencia),1,archAsis);
               }

    }

    fclose(archActual);
    fclose(archAsis);
    fclose(archInsc);

   }else{
    printf("algun archivo no existe");
   }


    listarArchivo();

    for(n = 0; n < i; n++){
        printf("%s\n",vecNoInscr[n]);
    }

    printf("Total Asistentes Inscriptos: %d",cantAsistentes);

    return 0;
}


void listarArchivo(){

    Asistencia asis;
    Inscriptos insc;
    Inscriptos actual;
    FILE *arch;

   //arch = fopen("asistenciaB.dat","rb");
    //arch = fopen("inscriptosB.dat","rb");
    arch = fopen("actualB.dat","rb");
    if(arch != NULL){

        //fread(&asis,sizeof(Asistencia),1,arch);
        //fread(&insc,sizeof(Inscriptos),1,arch);
        fread(&actual,sizeof(Inscriptos),1,arch);
        while(!feof(arch)){
           // printf("%s %s \n",asis.NroInsc,asis.apellido);
           // fread(&asis,sizeof(Asistencia),1,arch);
          // printf("%s %s %d \n",insc.NroInsc,insc.apellido,insc.cantInasis);
          // fread(&insc,sizeof(Inscriptos),1,arch);
          printf("%s %s %d \n",actual.NroInsc,actual.apellido,actual.cantInasis);
          fread(&actual,sizeof(Inscriptos),1,arch);
        }

        fclose(arch);
    }else{
        printf("el archivo no existe");
    }


}

void cargarAsistencias(){

    Asistencia asis;
    FILE *archT, *archB;

    archT = fopen("Asistencia.txt","r");
    archB = fopen("asistenciaB.dat","wb");

    if(archT != NULL){
        while(fscanf(archT,"%s %s",asis.NroInsc,asis.apellido) == 2){
            fwrite(&asis,sizeof(Asistencia),1,archB);
        }

        fclose(archB);
        fclose(archT);
    }else{

        printf("el archivo no existe");
    }


}


void cargarInscriptos(){

    Inscriptos insc;

    FILE *archT, *archB;

    archT = fopen("Inscriptos.txt","r");
    archB = fopen("inscriptosB.dat","wb");

    if(archT != NULL){
        while(fscanf(archT,"%s %s %d",insc.NroInsc,insc.apellido,&insc.cantInasis) == 3){
            fwrite(&insc,sizeof(Inscriptos),1,archB);
        }

        fclose(archB);
        fclose(archT);
    }else{

        printf("el archivo no existe");
    }


}
