//Alicia Vílchez Ceballos, ETSIIT (ugr)
/*
Ejercicio 5: Escribir un programa, similar a la orden cp, que utilice para su implementación la
llamada al sistema mmap() y una función de C que nos permite copiar memoria, como por
ejemplo memcpy(). Para conocer el tamaño del archivo origen podemos utilizar stat() y para
establecer el tamaño del archivo destino se puede usar ftruncate()
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
        struct stat sb; // seran los atributos del archivo a copiar
        off_t len;
        char *p, *p_d;
        int fd1, fd2;

        if (argc != 3) {
                printf("Uso: %s archivo_a_copiar archivo_copiado\n", argv[0]);
                exit(1);
        }

        fd1 = open (argv[1], O_RDONLY,  S_IRWXU);
        if (fd1 == -1) {
                printf("Error al abrir archivo\n");
                return 1;
        }
        fd2 = open (argv[2], O_CREAT | O_RDWR,  S_IRWXU);
        if (fd1 == -1) {
                printf("Error al abrir archivo\n");
                return 1;
        }

        if (fstat (fd1, &sb) == -1) {
                printf("Error al hacer stat\n");
                return 1;
        }

        if (!S_ISREG (sb.st_mode)) {
                printf ("%s : no es un archivo regular\n", argv[1]);
                return 1;
        }
        
        //asignamos espacio al fichero de destio
        ftruncate(fd2, sb.st_size);
        // llevamos a cabo la proyeccion
        p = (char *) mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd1, 0);
        if(p == MAP_FAILED) {
                 perror("Error en la proyeccion");
                 exit(2);
        }
        // llevamos a cabo la proyeccion de escritura en el fichero de destino
	p_d = (char *) mmap(0, sb.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);
        if(p_d == MAP_FAILED) {     
                perror("Fallo en la segunda proyeccion");
                exit(2);
        }
                
        //llevamos a cabo la copia
        memcpy(p_d, p, sb.st_size);

        // cerramos las proyecciones
        if (munmap (p, sb.st_size) == -1) {
                printf("Error al cerrar la proyeccion \n");
                return 1;
        }

          if (munmap (p_d, sb.st_size) == -1) {
                printf("Error al cerrar la proyeccion \n");
                return 1;
        }

        return 0;
}
					  
