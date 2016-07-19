/*
* programa1b.c
* uso:		./programa <nombreFicheroTexto>
* lee un fichero de texto y escribre en otro bloques de 80B encabezando cada bloque con el mensaje
* "Bloque i". En este programa además se añade un dato antes de cerrar el fichero
* de escritura al inicio del mismo.
*/
#define _GNU_SOURCE 1
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>



int main(int argc, char * argv[]){

int fdi,fdo,fd; //descriptores de archivo de escritura y lectura respectivamente
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

if((fdo=open("salida.txt",O_CREAT|O_TRUNC|O_RDWR,S_IRUSR|S_IWUSR))<0){
	printf("\nError %d en open",errno);
	perror("\nError open");
	exit(-1);
}


int i=1,tamEncabezado;
char buffer[80];
char encabezado[30];
char inicio[70];
int t;
int hole,data=70;
hole=sprintf(inicio , "El número de bloques es ");
write(fdo,inicio,(ssize_t)70);

while( (count = read(fdi,buffer,80)) > 0){
	//Escribimos en el archivo
	tamEncabezado = sprintf(encabezado, "Bloque %d\n",i);
	escrito=write(fdo,encabezado,(ssize_t)tamEncabezado);
	escrito=write(fdo,buffer,(ssize_t)count);
	i++;
}


if(lseek(fdo,hole,SEEK_SET) < 0) {
	perror("\nError en lseek");
	exit(EXIT_FAILURE);
}

off_t bytes;


char numBloques[30];
ssize_t tamNumBloques;
tamNumBloques = sprintf(numBloques,"%d\n",i);
escrito = write(fdo,numBloques,(ssize_t)tamNumBloques);

//Vamos borrando todos los huecos que hemos dejado
char borrado='\b';
for(i=0;i<data-hole-escrito;i++){
	write(fdo,&borrado,(ssize_t)1);
}



close(fdi);
close(fdo);


return EXIT_SUCCESS;
}

