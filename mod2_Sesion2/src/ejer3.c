// Ana Alicia Vílchez Ceballos, ejer3.c
// en este ejercicio trataremos con la apertura de los ficheros de un directorio,
// queda prohibido utilizar la función nftw
	
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>		//Needed for open
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.
#include <string.h>

int n_archivosr = 0;
double tam_archr = 0;
//vamos a crear una funcion que recorra directorios y subdirectorios de forma recursiva y en caso de que se
//encuentren los archivos con las correspondientes características los imprime
void recorreDirectorio(char *ruta, char *nombre){

	DIR *dirp;
	struct dirent *direntp;
	struct stat atributos;

	// Esto es para sacar el nombre completo de la ruta donde se encuentra el archivo
  	char nombrecompleto[strlen(ruta)+strlen(nombre)+2]; // Sumamos 2, por el \0 y la barra de directorios (/) no sabemos si falta 

	if(ruta[strlen(ruta) -1] =='/')
		sprintf(nombrecompleto,"%s%s", ruta, nombre);
	    
	else
		sprintf(nombrecompleto,"%s/%s", ruta, nombre);

	// aqui abrimos el directorio
	dirp = opendir(nombrecompleto);
 	if (dirp == NULL){
 		printf("Error: No se puede abrir el directorio\n");
 		exit(2);
 	} 
	
	while((direntp = readdir(dirp)) != NULL) {
 		//obtenemos los atributos de cada archivo dentro del directorio
 		stat(direntp->d_name, &atributos) ;

		if(direntp->d_type == DT_DIR){ // si es un directorio volvemos a llamar a la funcion
			if(strcmp(direntp->d_name,".") != 0 && strcmp(direntp->d_name,"..") != 0){
				recorreDirectorio(nombrecompleto, direntp->d_name);
			}
		}
		else if(S_ISREG(atributos.st_mode) && (atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){
			printf("%s\t%d\n", direntp->d_name, direntp->d_ino);
			n_archivosr+=1;
			tam_archr += direntp->d_reclen;
		}
 	} // fin while
 	
} // fin funcion


int main(int argc, char *argv[]){

	DIR *dirp;
	struct dirent *direntp;
	struct stat atributos;

	// abrimos el directorio (si no le pasamos argumentos, cogemos como directorio el)
	
	dirp = opendir(argv[1]);
	if (dirp == NULL){
		printf("Error: No se puede abrir el directorio\n");
		exit(2);
	} 
	 
 	/* Leemos las entradas del directorio */
	printf("Los i nodos son:\n");
 	while((direntp = readdir(dirp)) != NULL) {

 		
	 	// Esto es para sacar el nombre completo de la ruta donde se encuentra el archivo
	 	char *ruta = argv[1];
	  	char nombrecompleto[strlen(ruta)+strlen(direntp->d_name)+2]; // /* Sumamos 2, por el \0 y la barra de directorios (/) no sabemos si falta */

		if (ruta[strlen(ruta) -1] =='/')
			sprintf(nombrecompleto,"%s%s", ruta, direntp->d_name);
		else
			sprintf(nombrecompleto,"%s/%s", ruta, direntp->d_name);
		
 		//obtenemos los atributos de cada archivo dentro del directorio
 		stat(nombrecompleto,&atributos) ;

		if(S_ISREG(atributos.st_mode) && (atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){ // Si el archivo es regular y tiene permisos de ejecucucion para grupos y para otros
			printf("%s\t%d\n", direntp->d_name, direntp->d_ino);
			n_archivosr += 1;
			tam_archr += direntp->d_reclen;
		} 

		else if(direntp->d_type == DT_DIR){ // si es un directorio llamamos a la funcion
			if(strcmp(direntp->d_name,".") != 0 && strcmp(direntp->d_name,"..") != 0)
				recorreDirectorio(argv[1], direntp->d_name);
		}
		
		
		
 	} // fin while

 	printf("\nExisten %d archivos regulares con permiso x para grupo y otros\n", n_archivosr);
 	printf("El tamanio total ocupado por dichos archivos es de %7.2f bytes \n", tam_archr/8);


 	return 0;
}
