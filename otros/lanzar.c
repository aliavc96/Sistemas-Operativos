
//Alicia Vílchez Ceballos ETSIIT (ugr)
/*
En este programa lo que se hace es que se pide una serie de i_nodos desde la entrada estandar.
De modo que por cada i_nodo que le pasamos, se crea un hijo que lanza el programa chequear y 
pasandole el nodo por la entrada estándar a través de un cauce sin nombre.

Con otro cauce se recogerá la salida estándar del programa chequear, y será el padre el que muestre 
(Con otro cauce sin nombre) y será el padre el que muestre los datos obtenidos en el cauce.


*/


#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Error en el numero de argumentos, por favor introduce un inodo como minimo\n");
		exit(1);
	}

	int fd1[2]; // cauce para almacenar el resultado del programa a lanzar
	int fd2[2]; // cauce para almacenar el argumento
	pid_t PID;

	int estado;
	

	for(int i = 1; i < argc; i++){ 

		pipe(fd1);
		pipe(fd2);
		
		if((PID = fork()) == 0){

			//duplicamos la entrada estandar para que coja los datos chequear de fd2[1]
			close(fd2[1]); //puesto que no vamos a escribir sino a leer
			dup2(fd2[0], STDIN_FILENO);

			//Cerrar el descriptor de lectura donde se almacenara el resultado del programa
			close(fd1[0]);
			//duplicamos para que la salida estandar vaya al cauce
			dup2(fd1[1], STDOUT_FILENO);

			//Lanzamos el programa que queremos ejecutar
			execl("./chequear","chequear", NULL);
		}

		else{

		
			close(fd2[0]); // cerramos el descriptor de lectura pues solo vamos a escribir
			dup2(fd2[1], STDIN_FILENO);
			
			if((write(fd2[1], argv[i],strlen(argv[i])+1)) < 0){
				perror("Error al escribir los argumentos\n");
				exit(1);
			}
			//printf("argumento aqui: %s\n",argv[i]);
			close(fd1[1]); // cerramos el descriptor de escritura pues solo vamos a leer de este cauce
			char resultado[2048];
			if((read(fd1[0], resultado, 2048)) < 0){
				perror("Error al leer el resultado\n");
				exit(1);
			}

			printf("Resultado obtenido:\n%s\n", resultado);
		}
	
	}

	wait(&estado); //para que no queden procesos zombies

}
