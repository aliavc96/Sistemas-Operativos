/*
Autora: Ana Alicia Vílchez Ceballos

ejer4.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
		       */
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
			   // aqui construimos la macro
#define S_REGULAR(mode) (((mode) & S_IFREG) == 0100000) // un numero multiplicado por si mismo, da ese numero (en este caso
							// en binario)
int main(int argc, char *argv[])
{

int i;
struct stat atributos;
char tipoArchivo[30];

if(argc<2) {
	printf("\nComo minimo se exige un argumento");
	exit(-1);
}
for(i=1;i<argc;i++) {
	printf("%s: ", argv[i]);
	if(lstat(argv[i],&atributos) < 0) { // aqui es donde asociamos el struct de tipo stat con los atributos del archivo que le pasamos como argumento
		printf("\nError al intentar acceder a los atributos de %s",argv[i]);
		perror("\nError en lstat");
	}
	else {
		if(S_REGULAR(atributos.st_mode)) 
			sprintf(tipoArchivo, "el archivo %s es regular\n", argv[i]);
		
		else
			sprintf(tipoArchivo, "el archivo %s NO es regular\n", argv[i]);

		printf("%s\n",tipoArchivo);
	}
}

return 0;
}
