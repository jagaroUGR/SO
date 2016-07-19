/*
* programa1.c
* uso:		./programa <nombreFicheroTexto>
* lee un fichero de texto y escribre en otro bloques de 80B encabezando cada bloque con el mensaje
* "Bloque i"
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>



int main(int argc, char * argv[]){

int fdi,fdo; //descriptores de archivo de escritura y lectura respectivamente
ssize_t count,escrito;


if(argc < 2){
	printf("Debe de especificarse un archivo de texto\n"); 
	exit(-1);
}

if( (fdi=open(argv[1],O_RDONLY))<0){
	printf("\nError %d en open",errno);
	perror("\nError open");
	exit(-1);
}

if((fdo=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0){
	printf("\nError %d en open",errno);
	perror("\nError open");
	exit(-1);
}


int i=1,tamEncabezado;
char buffer[80];
char encabezado[30];

while( (count = read(fdi,buffer,80)) > 0){
	//Escribimos en el archivo
	tamEncabezado = sprintf(encabezado, "Bloque %d\n",i);
	escrito=write(fdo,encabezado,(ssize_t)tamEncabezado);
	escrito=write(fdo,buffer,(ssize_t)count);
	i++;
}

close(fdo);
close(fdi);

return EXIT_SUCCESS;
}

