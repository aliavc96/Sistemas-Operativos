//Ana Alicia Vílchez Ceballos, ejer3.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	pid_t childpid;
	int nprocs = 20;
	/*
	// jerarquia de procesos de tipo 1
	for(int i = 1; i < nprocs; i++){
		if((childpid = fork()) == -1){
			perror("\nError en el fork");
			exit(-1);
		}
		printf("ejecutado por %d\n", getpid());
		if(childpid)
			break;
	}
*/
	// jerarquia de procesos de tipo 1
	for(int i = 1; i < nprocs; i++){
		if((childpid = fork()) == -1){
			perror("\nError en el fork");
			exit(-1);
		}
		printf("ejecutado por %d como hijo y %d como padre\n", getpid(), getppid());
		if(!childpid)
			break;
	}
	
}