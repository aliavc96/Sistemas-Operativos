
// ejercicio1.c
/*
Ejercicio 1. Implementa un programa que admita t argumentos. El primer argumento será una
orden de Linux; el segundo, uno de los siguientes caracteres “<” o “>”, y el tercero el nombre de
un archivo (que puede existir o no). El programa ejecutará la orden que se especifica como
argumento primero e implementará la redirección especificada por el segundo argumento hacia
el archivo indicado en el tercer argumento.
*/
// precondición: cuando le pasemos el segundo argumento, es decir, > o < hay que ponerlo
// entrecomillado ya que si no, lo toma como redirección.

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char * argv[]){


	if(argc < 4){
		printf("Error en el numero de argumentos\n");
		printf("pasar como argumentos: orden </> archivo\n");
		exit(-1);
	}
	
	if(strcmp(argv[2],"<") != 0 && strcmp(argv[2],">") != 0){
		printf("Error en el segundo parámetro\n");
		exit(2);
	}

	int fd ;
	if((fd = open(argv[3],O_CREAT | O_WRONLY, S_IRWXU)) < 0){
		printf("error al abrir el archivo\n");
		exit(1);
	}

	if(strcmp(argv[2],">") == 0){
		close(1); // cerramos la salida estandar para llevar a cabo la duplicacion
		
		if(fcntl(fd, F_DUPFD,1) == -1){
			perror("fallo en fcntl");
			exit(1);
		}
		char buffer[256];
		execlp(argv[1], argv[1], NULL); // escribe en el archivo que se ha abierto

		int cont = write(1,buffer,256);
	}
	//En este programa execlp no recibirá argumentos!!!
	// Para este caso, el fichero si tiene algo escrito, será un argumento del comando
	else{
		// En este caso lo que tenemos que hacer es cerrar la entrada estándar para que el proceso
		// pueda leer del archivo y así tomar el contenido del archivo como argumento para el comando 
		// que le pasamos como primer parámetro
		close(0); // cerramos la entrada estandar para llevar a cabo la duplicacion

		if(fcntl(fd, F_DUPFD,0) == -1){ // duplicamos el descriptor en el "hueco" de la entrada estándar
			perror("fallo en fcntl"); 
			exit(1);
		}
	
		execlp(argv[1], argv[1],NULL); 

	}
	return 0;



}
