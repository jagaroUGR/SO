/*
* Progama2.c
* Uso: ./programa2 <archivo>
* El programa imprime si el archivo es regular usando una macro
*/

#include<sys/stat.h>

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h> 

#define S_ISREG2(mode) ( ( (mode & 32768) == 32768) ?(1):(0)) 

int main(int argc, char * argv[]){

struct stat atributos;

if(argc !=2){
	perror("\nDebe de indicarse un archivo");
	exit(-1);
}

	if(lstat(argv[1],&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de %s",argv[1]);
		perror("\nError en lstat");
	
	}

	if(S_ISREG2(atributos.st_mode))
		printf("El archivo es regular\n");
	else
		printf("El archivo NO es regular\n");




return EXIT_SUCCESS;

}
