
//Alicia Vílchez Ceballos ETSIIT (ugr)
/*
En este programa le pasamos un archivo como argumento
y vamos comprobando si la longitud de ese archivo va variando en un bucle infinito.
En caso de que varie, lanzamos un mensaje a la salida estándar.
*/






#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>		//Needed for open
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
int main(int argc, char *argv[]){

	//lO QUE VAMOS A HACER ES LEER LOS BYTES DE UN ARCHIVO Y LUEGO VER SI VA VARIANDO EN UN BUCLE INFINITO
	if(argc < 2){
		printf("ERROR: el numero de argumentos es incrorrecto\n escribe %s ruta_archivo\n", argv[0]);
		exit(1);
	}
	
	struct stat atributos;
	if(stat(argv[1], &atributos) < 0){
		printf("Error al acceder a los atributos del archivo\n");
		exit(3);
	}
	if(!S_ISREG(atributos.st_mode)){
		printf("Error: el archivo pasado como argumento no es regular\n");
		exit(4);
	}
	off_t bytesIniciales = atributos.st_size;
	
	while(1){
		if(stat(argv[1], &atributos) < 0){
			printf("Error al acceder a los atributos del archivo\n");
			exit(3);
		}

		if(bytesIniciales != atributos.st_size){ //comprobamos si ha variado la longitud
			int diferencia  =  atributos.st_size - bytesIniciales;
			printf("%10d\n", diferencia);
			bytesIniciales = atributos.st_size;
		}
	}

	return(0);
}
