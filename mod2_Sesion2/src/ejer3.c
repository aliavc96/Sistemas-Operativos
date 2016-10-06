// en este ejercicio trataremos con la apertura de los ficheros de un directorio,
// la  modificación de los permisos y obtencion de sus atributos.
	
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>		//Needed for open
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.

#define S_REGULAR(mode) (((mode) & S_IFREG) == 0100000) // un numero multiplicado por si mismo, da ese numero


int main(int argc, char *argv[]){

	DIR *dirp;
	struct dirent *direntp;
	struct stat atributos;

	if(argc < 2){
		printf("error en el numero de argumentos: %d\n", argc);
		exit(1);
	}
	// abrimos el directorio
	dirp = opendir(argv[1]);
 	if (dirp == NULL){
 		printf("Error: No se puede abrir el directorio\n");
 		exit(2);
 	} 

 	int n_archivosr = 0;
 	double tam_archr = 0;
 	/* Leemos las entradas del directorio */
	printf("Los i nodos son:\n");
 	while((direntp = readdir(dirp)) != NULL) {
 		//obtenemos los atributos de cada archivo dentro del directorio

 		stat(direntp->d_name,&atributos) ;
			
		if(S_REGULAR(atributos.st_mode) && (atributos.st_mode & (S_IXGRP | S_IXOTH) == (S_IXGRP | S_IXOTH))){ // Si el archivo es regular y tiene permisos de ejecucucion para grupos y para otros
			printf("%s\t%d\n", direntp->d_name, direntp->d_ino);
			n_archivosr += 1;
			tam_archr += direntp->d_reclen;

		} 
 	}
 	printf("\nExisten %d archivos regulares con permiso x para grupo y otros\n", n_archivosr);
 	printf("El tamanio total ocupado por dichos archivos es de %7.2f bytes \n", tam_archr/8);


 	return 0;
}