// Ana Alicia Vílchez Ceballos, ejer1.c
// Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"

// precondición: el argumento que le pasamos debe ser un numero entero

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int var;
	pid_t pid;

	if(argc < 2){
		perror("\nError en el numero de argumentos");
		exit(-2);
	}

	int num = atoi(argv[1]);

	if( (pid=fork()) < 0) {
		perror("\nError en el fork");
		exit(-1);
	}

	if(pid == 0){
		if(num % 2 == 0 )
			printf("el numero %d es PAR (hecho por proceso %d)\n", num, getpid());
		else
			printf("el numero %d es IMPAR (hecho por proceso %d)\n", num, getpid());	
	}

	else{ // en caso es el proceso padre, pues el PID es distinto de 0
		if(num % 4 == 0 )
			printf("el numero %d es divisible por 4 (hecho por proceso %d)\n", num, getpid());
		else
			printf("el numero %d NO es divisible por 4 (hecho por proceso %d)\n", num, getpid());
	}
}