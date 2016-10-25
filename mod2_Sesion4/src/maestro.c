/*
Ana Alicia Vilchez Ceballos, ETSIIT(UGR)
tarea8.c
Programa del maestro esclavo llevando a cabo el uso de pipes y la redirección de entrada y
salida
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int fd1[2]; // cauce de comunica ción entre el maestro y el primer esclavo
	int fd2[2]; // cauce de comunicación entre el maestro y el segundo esclavo
	pid_t PID;

	pipe(fd1); // Llamada al sistema para crear un pipe
	pipe(fd2); // Llamada al sistema para crear un pipe
	char cadena[10];

	char buffer[80]; // almacenamos los datos de la primer ejecucion del programa esclavo
	char buffer2[80]; // almacenamos los datos de la segunda ejecucion del programa esclavo
	int extremo_anterior = atoi(argv[1]);
	int extremo_posterior = atoi(argv[2]);
	// calculamos el intervalo que le deberemos pasar al programa esclavo
	int mitad = (extremo_posterior - extremo_anterior)/2;

	if ( (PID= fork())<0) { // creamos el primer proceso hijo
		perror("\Error en fork");
		exit(-1);
	}
	

	if (PID == 0) { 
		//Cerrar el descriptor de lectura en cauce situado en el proceso hijo
		close(fd1[0]);
			
		//Duplicar el descriptor de escritura de cauce en el descriptor
		//correspondiente a la salida estandar, cerrado previamente en
		//la misma operación
		close(STDOUT_FILENO);
		dup(fd1[1]);

		sprintf(cadena, "%d", extremo_anterior+mitad);
		execlp("./esclavo","esclavo",argv[1], cadena, NULL);

	}
	else{
		if( (PID= fork())<0) { // creamos el segundo proceso hijo
			perror("\Error en fork");
			exit(-1);
		}
	

		if(PID == 0){
			//Cerrar el descriptor de lectura en cauce situado en el proceso hijo
			close(fd2[0]);
			
			//Duplicar el descriptor de escritura de cauce en el descriptor
			//correspondiente a la salida estandar, cerrado previamente en
			//la misma operación
			close(STDOUT_FILENO);
			dup(fd2[1]);
		
			sprintf(cadena, "%d", extremo_anterior+mitad+1);
			execlp("./esclavo","esclavo",cadena, argv[2], NULL);
			printf("Entra en el else if\n");
			
		}
		else{ // proceso padre------------>
			printf("Aqui se muestran los numeros primos del rango [%d,%d]:\n",extremo_anterior, extremo_posterior);
			//Cerrar el descriptor de ESCRITURA en el proceso padre
			close(fd1[1]);
			
			//Duplicar el descriptor de lectura en cauce en el descriptor
			//correspondiente a la salida estda r (stdout), cerrado previamente en
			//la misma operación
			close(STDIN_FILENO);
			dup(fd1[0]);
			
			// ahora leemos de fd1[0]
			while(read(fd1[0],&buffer, 80) > 0){
				printf("%s", buffer);
			}
			

			//Cerrar el descriptor de ESCRITURA en el proceso padre
			close(fd2[1]);

			//Duplicar el descriptor de lectura en cauce en el descriptor
			//correspondiente a la salida estda r (stdout), cerrado previamente en
			//la misma operación
			close(STDIN_FILENO);
			dup(fd2[0]);

			// ahora leemos de fd2[0]
			while(read(fd2[0],&buffer2, 80) > 0){
				printf("%s", buffer2);
			}
		}
	}

	return(0);
}
