/*
ejer2.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
// este ejercicio no está del todo bien y no se por qué

*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>



// aqui reservamos 80 casillas en el vector
//buf1= (int*)malloc(80*sizeof(int));

int main(int argc, char *argv[])
{

	char cadena[7];
	char cadena1[22];
	char buf1[80];
	int fd;
	int fx;
	int grupo = 1;

	// aqui detectamos si se trata de la salida estandar o si es de un fichero 
	if(argc > 1){

		if( (fd=open(argv[1],O_RDONLY))<0) {
				printf("\nError %d en open",errno);
				perror("\nError en open");
				exit(EXIT_FAILURE);
		}
	}

    else
    	fd = STDIN_FILENO;

	if( (fx=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR | S_IRWXU))<0) {
			printf("\nError %d en open",errno);
			perror("\nError en open");
			exit(EXIT_FAILURE);
	}

	// esto se lo he puesto para meter la frase al principio, ya que si no lo pongo
	//pisaria lo primero que se escribe

	if((write(fx,"eeeeeeeeeeeeeeeeeeeeee",22)) < 0) {  // este \n lo pongo para que luego cuando volvamos al principio del fichero con lseek pueda escribir el numero de grupos
			perror("\nError en el tercer write");
			exit(EXIT_FAILURE);
	}
	

	while(read(fd,&buf1, 80) > 0){

		sprintf(cadena, "Grupo %i", grupo);
			
		
		if((write(fx,cadena,7)) < 0) {
			perror("\nError en el primer write");
			exit(EXIT_FAILURE);
		}

		if((write(fx,"\n",1)) < 0) { 
			perror("\nError en el 5 write");
			exit(EXIT_FAILURE);
		}
			
		if((write(fx,buf1,80)) < 0) {
			perror("\nError en segundo write");
			exit(EXIT_FAILURE);
		}
			
		if((write(fx,"\n\n",2)) < 0) {
			perror("\nError en el tercer write");
			exit(EXIT_FAILURE);
		}

		grupo += 1;
	}

	// MODIFICACIÓN ADICIONAL:
	sprintf(cadena1, "grupos producidos: %i\n", grupo);

	if(lseek(fx,0,SEEK_SET) < 0){ // seek_set marca el inicio del fichero
		perror("\nError en lseek");
		exit(-1);
	}

	if((write(fx,cadena1,sizeof(cadena1))) < 0) {
		perror("\nError en el 6 write");
		exit(EXIT_FAILURE);
	}


		
	
	return EXIT_SUCCESS;
}
