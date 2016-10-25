//Ana Alicia Vílchez Ceballos, ejer4.c y ejercicio 5 (que include una modificación del 4)
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// variables globales:
int nprocs = 5;


void finalizar(pid_t *pid){

// Con este código llevamos a cabo la modicifación propuesta en el ejercicio 5, donde se espera primero a los 
// hijos creados en orden impar y luego amlos que tienen orden par
/*
	for (int i=0; i<nprocs; i++) {
		if(i %2 != 0){
			if (waitpid(pid[i],0,0) > 0) {   // si la espera ha tenido exito y finaliza el hijo tal...         
				printf("Acaba de finalizar mi hijo %d (orden %d)\n",pid[i], i);
				printf("Solo me quedan %d hijos vivos\n",nprocs - i -1);
      			}
      		}
	}

	for (int i=0; i<nprocs; i++) {
		if(i %2 == 0){
			if (waitpid(pid[i],0,0) > 0) {   // si la espera ha tenido exito y finaliza el hijo tal...         
				printf("Acaba de finalizar mi hijo %d (orden %d)\n",pid[i], i);
				printf("Solo me quedan %d hijos vivos\n",nprocs - i -1);
      			}
      		}
	}
*/
	for (int i=0; i<nprocs; i++) {
		if (waitpid(pid[i],0,0) > 0) {   // si la espera ha tenido exito y finaliza el hijo tal...         
			printf("Acaba de finalizar mi hijo %d (orden %d)\n",pid[i], i);
			printf("Solo me quedan %d hijos vivos\n",nprocs - i -1);
      		}
      	
	}
	
}

int main(int argc, char *argv[]){

	pid_t pid[nprocs];
	

	if ((pid[0] = fork())==0) // el proceso padre invoca al hijo
		printf("\nsoy el hijo %d\n", getpid());
		
		
		else {
			
			if((pid[1] = fork()) == 0){
				printf("\nsoy el hijo %d\n", getpid());// si no es el hijo el proceso padre vuelve a invocar al hijo y continua con el código finalizar(pid)
			}
			else {
				if((pid[2] = fork()) == 0){
					printf("\nsoy el hijo %d\n", getpid());// Proceso hijo
				}
				else {
					if((pid[3] = fork()) == 0){
						printf("\nsoy el hijo %d\n", getpid());// Proceso hijo
					}
					else {
						
						if((pid[4] = fork()) == 0){
							printf("\nsoy el hijo %d\n", getpid());// Proceso hijo
						}
					}
				}
			}
		
		}

	
	finalizar(pid);

	
}
