#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

main(int arg, char *argv[])
{

	char *archivos[60] ;
  evaluarDir(archivos,argv[1]);

	
}



	void evaluarDir(char *archivos[], char directorio[100])
	{
	struct dirent **entradas= NULL;

	
	int numeroEntradas = scandir (directorio, &entradas, NULL, NULL);
	

	char destino[120];
	

	

	for (int i=0; i<numeroEntradas; i++)
	{
		if(entradas[i]->d_type == DT_REG)
		{	
		strcat(destino,directorio);
		strcat(destino,"/");
		
		
		archivos[i] = entradas[i]->d_name;
		printf ("%s\n", archivos[i]);
		strcat(destino,archivos[i]);
		printf ("%d\n",filesize(destino));
		destino[0] = '\0';
		free (entradas[i]);
		entradas[i] = NULL;
		}
		
	}

	
	free (entradas);
	entradas = NULL;
	}




int filesize(char *filename) {
        // Definicion e inicializacion de variables
        FILE *fp;
        int count = 0;

        // Se abre el archivo y se contara caracter por caracter el numero 
        // de bytes del archivo
        fp = fopen(filename,"r");
        if (fp == NULL) {
                perror("filesize - No se pudo abrir archivo\n");
                return -1;
        }
        while (fgetc(fp) != EOF) {
                count++;
        }
        fclose(fp);
        return count;
}

