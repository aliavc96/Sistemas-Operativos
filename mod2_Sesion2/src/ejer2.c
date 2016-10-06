// en este ejercicio trataremso con la apretura, modificación de los permisos de sus ficheros y obtencion de sus atributos
	
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>		//Needed for open
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.


//Función que permite imprimir los permisos
void imprimir (struct stat estru){
 printf( (S_ISDIR(estru.st_mode)) ? "d" : "-" );
 printf( (estru.st_mode & S_IRUSR) ? "r" : "-" );
 printf( (estru.st_mode & S_IWUSR) ? "w" : "-" );
 printf( (estru.st_mode & S_IXUSR) ? "x" : "-" );
 printf( (estru.st_mode & S_IRGRP) ? "r" : "-" );
 printf( (estru.st_mode & S_IWGRP) ? "w" : "-" );
 printf( (estru.st_mode & S_IXGRP) ? "x" : "-" );
 printf( (estru.st_mode & S_IROTH) ? "r" : "-" );
 printf( (estru.st_mode & S_IWOTH) ? "w" : "-" );
 printf( (estru.st_mode & S_IXOTH) ? "x" : "-" );
 printf("%-3s");
}


int main(int argc, char *argv[]){

	DIR *dirp;
	struct dirent *direntp;
	struct stat atributos;

	if(argc < 3){
		printf("error en el numero de argumentos: %d\n", argc);
		exit(1);
	}
	// abrimos el directorio
	dirp = opendir(argv[1]);
 	if (dirp == NULL){
 		printf("Error: No se puede abrir el directorio\n");
 		exit(2);
 	} 

 	// convertimos la mascara pasada como argumento en un entero con strol
 	int base;
 	char *finalPtr;
 	strtol(argv[2], &finalPtr, base) ;

 	/* Leemos las entradas del directorio */
	printf("nombre_archivo\tpermisos antes\tpermisos despues\n");
 	while((direntp = readdir(dirp)) != NULL) {

 		stat(direntp->d_name, &atributos);
 		printf("%s\t", direntp->d_name);

 		imprimir(atributos);
 		printf("\t");
 		if(chmod(direntp->d_name, base) < 0) 
			printf("Error\t");
		else
			imprimir(atributos);
 		
 		printf("\n");
 	}

 	return 0;
}