//Jhon Alejandro Orobio Arce 201533627

//Carolina Dorado Ruiz 201522589

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

main(int arg, char *argv[])
{



	char *archivos[60];


	evaluarDir(archivos,argv[1]);




	
}

	void evaluarDir(char *archivos[60], char directorio[100])
	{

	

	struct dirent **entradas= NULL;

	pid_t pid;
	int numeroEntradas = scandir (directorio, &entradas, NULL, NULL);


	char desti[100];
	int contador = 0;
	int contador2 = 0;
	int tope = (int) numeroEntradas/2;
	int ini = ((int) numeroEntradas/2)+1;
	int fd[2];

	pipe(fd);

	if((pid = fork()))
	{
		int contahijo = 0;
		int contahijo2 = 0;
		close(fd[1]);

		for (int j=0; j<=tope; j++)
		{

			if(entradas[j]->d_type == DT_REG)
			{

				for (int i = 0; i<100;i++)
					{
						desti[i] = directorio[i];
					}

				strcat(desti,"/");
				archivos[j]= entradas[j]->d_name;
				strcat(desti,archivos[j]);
				contador += filesize(desti);
				desti[0] = '\0';
				contador2++;

				free (entradas[j]);
				entradas[j] = NULL;

			}


			}

		read(fd[0],&contahijo,sizeof(contahijo));
		printf ("Numero de archivos: %d + %d = %d\n",contador2, contahijo,contador2+contahijo);
		read(fd[0],&contahijo2,sizeof(contahijo2));
		printf ("Peso total: %d + %d = %d bytes\n",contador, contahijo2,contador+contahijo2);
		

	}

		else
		{
			close(fd[0]);


					for (int i=ini ; i< numeroEntradas; i++)
					{


						if(entradas[i]->d_type == DT_REG)
						{

							for (int i = 0; i<100;i++)
								{
									desti[i] = directorio[i];
								}

							strcat(desti,"/");
							archivos[i]= entradas[i]->d_name;

							strcat(desti,archivos[i]);
							contador += filesize(desti);
							desti[0] = '\0';
							contador2++;

							free (entradas[i]);
							entradas[i] = NULL;

						}
					}

					write(fd[1],&contador2,sizeof(contador2));
					write(fd[1],&contador,sizeof(contador));



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
        	printf("%s\n", filename);
                perror("filesize - No se pudo abrir archivo\n");
                return -1;
        }
        while (fgetc(fp) != EOF) {
                count++;
        }
        fclose(fp);
        //printf("%d\n", count);

        return count;
}

