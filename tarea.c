#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

main(int arg, char *argv[])
{

	clock_t start = clock();

	char *archivos[60];

	infoDir(archivos,argv[1]);

	printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);

	
}



	int evaluarDir(char *archivos[], char directorio[100])
	{
	struct dirent **entradas= NULL;

	
	int numeroEntradas = scandir (directorio, &entradas, NULL, NULL);
	


	int contador = 0;

	

	for (int i=0; i<numeroEntradas; i++)
	{
		if(entradas[i]->d_type == DT_REG)
		{	
		
		archivos[i] = entradas[i]->d_name;
		printf ("%s\n", archivos[i]);
		free (entradas[i]);
		entradas[i] = NULL;
		}
		
	}
	
	return numeroEntradas;

	free (entradas);
	entradas = NULL;
	}


	void infoDir(char *archivos[], char directorio[100])
		{



			char destino[120];
			int contador = 0;

			evaluarDir(archivos,directorio);


			for (int i=0; i<numeroEntradas; i++)
			{

				strcat(destino,directorio);
				strcat(destino,"/");
				strcat(destino,archivos[i]);
				printf ("%s\n", destino);
				contador += filesize(destino);
				destino[0] = '\0';



			}

			printf ("Peso total: %d\n",contador);


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

