// Alicia Vilchez Ceballos, ETSIIT (ugr)

/*
// Fichero para el examen del Modulo 2 de Sistemas Operativos de diciembre de 2015
// El ejercicio viene a ser que le pasamos un numero de i_nodo por la entrada estandar,
// el programa abre el directorio $HOME y comprueba si el i_nodo se corresponde con alguno de los i_nodos
// que se encuentran dentro del directorio. En caso de que haya coincidencias nos dará el nombre del archivo
// y el uid del propietario.
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


	DIR *dirp;
	struct dirent *direntp;
	struct stat atributos;
	char *home = getenv("HOME");
	int coincidencias = 0;
	dirp = opendir(home); //abrimso el directorio $HOME
 	if (dirp == NULL){
 		printf("Error: No se puede abrir el directorio\n");
 		exit(2);
 	} 
 	char cadena[25];

 	//Leemos el inodo de la entrada estandar
	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}
	read(STDIN_FILENO, cadena, 7);
 	int inodo = atoi(cadena);

 	while((direntp = readdir(dirp)) != NULL){
 		char nombrecompleto[50];
 		
		sprintf(nombrecompleto,"%s/%s", home, direntp->d_name);
		
		//aqui obtenemos los atributos de cada archivo
		if((direntp->d_name)[0] != '.'){
		
			if(stat(nombrecompleto, &atributos) < 0)
				printf("Error al abrir los atributos del archivo\n");
				
			if(atributos.st_ino == inodo){
				printf("UID del propietario: %d\tnombre del archivo: %s\n", (int)atributos.st_ino,direntp->d_name);
				coincidencias++;
			}
		}
		
 	}
 	closedir(dirp);

 	if(coincidencias > 0)
 		return(EXIT_SUCCESS);
 	else
 		return(EXIT_FAILURE);
 	
}
