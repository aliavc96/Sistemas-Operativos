//tarea5.c
//Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
/*
En este programa lo que llevamos a cabo es la creación de un proceso hijo que se encargará de ejecutar 
la orden ldd que se encuentra en el directorio /usr/bin/ y que nos muestra las librerías que 
necesita un programa, en este caso tarea5
el ultimo argumento será NULL pues siempre va detrás de la lista de parámtros, en este caso el único 
parámetro que necesita lls es el ejecutable de ./tarea5
La llamada wait recibe como parámetro un puntero a entero donde se deposita el valor devuelto por 
el proceso hijo al terminar; y retorna el PID del hijo. 
Por tanto el código siguiente a la ejecución de lld no la realiza el hijo creado con fork() sino el padre.



*/

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	int estado;

	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);
	}
	else if(pid==0) {  //proceso hijo ejecutando el programa
		if( (execl("/usr/bin/ldd","ldd","./tarea5", NULL)<0)) {
			perror("\nError en el execl");
			exit(-1);
		}
	}
	wait(&estado);
	printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado);

	exit(0);

}