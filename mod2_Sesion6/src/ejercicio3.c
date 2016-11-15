
/*
Ana Alicia Vílchez Ceballos, ETSIIT (ugr)


Ejercicio que demuestra que el kernel es capaz de detectar y solucionar el interbloqueo.

Lanzamos el programa desde dos terminales para llevar a cabo varios procesos sobre dos archivos
de modo que todos los procesos invocados se queden esperando por bloquear dichos archivos
que les pasamos como argumento


*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char * argv[]) 
{
	if(argc < 3){
		printf("Error en el numero de argumentos\n");
		exit(1);
	}
	char cadena[3];
	int fd[2];
	int i = 0;

	// abrimos el archivo	
	if ((fd[0] = open(argv[1], O_RDWR, S_IRWXU)) == -1 ){
		perror(" fallo en open \n");
		exit(1);
	}

	if ((fd[1] = open(argv[2], O_RDWR, S_IRWXU)) == -1 ){
		perror(" fallo en open \n");
		exit(1);
	}	

	while(i < argc){
		

		/* intentamos un bloqueo de escritura  archivo */
		struct flock cerrojo;
		cerrojo.l_type=F_WRLCK;
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		cerrojo.l_len=0;

		printf("tratando de bloquear el archivo...%d\n", i);
		if((fcntl (fd[i], F_SETLKW, &cerrojo) )== -1) {
		           if(errno == EDEADLK)
		               printf("ATENCION: interbloqueo detectado \n");
		           else{
		           		printf("ATENCION: error detectado \n");
		           		exit(1);
		           }

		}

			
		printf("El cerrojo puesto sobre %s ha tenido exito \n", argv[1]);
		printf("Introduzca una letra\n");
		gets(cadena);

		i++;
		
	}
	
	
	return 0;
}
