#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(void){
	pid_t proceso;
	pid_t procesoP;

	proceso = geteuid(); // usuario efectivo
	procesoP = getuid(); // usuario real

	printf("iden del usuario efectivo %d\n", proceso);
	printf("iden del usuario real %d\n", procesoP);

}