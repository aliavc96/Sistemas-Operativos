/*
programa esclavo para el ejercicio 5 de la sesión 4 
Trabajo con llamadas al sistema del Subsistema de Procesos y Cauces conforme a POSIX 2.10
// para compilar este programa hacer: gcc esclavo.c -lm -o esclavo
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{

	int extremo_anterior = atoi(argv[1]);
	int extremo_posterior = atoi(argv[2]);

	for(int i = extremo_anterior; i < extremo_posterior; i++){
		int d = 0;
		for(int k=1; k < i; k++){
			if(i%k == 0) // contabilizamos sus divisores y si son > 2 es porque no es 
				d++;	//  primo

		}
		if(i != 1 && d < 2) // pues el 1 no puede ser nunca divisor
			printf("%d\n", i);
	}

	return(0);
}

