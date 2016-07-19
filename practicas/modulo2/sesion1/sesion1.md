#Módulo 2 Sesión I. Llamadas al sistema para el SA

##1.Entrada y salida de archivos regulares

En esta sección usaremos las llamadas:

* open
* read
* write
* lseek
* close

###Llamada al sistema open

``` c
int open(const char \*pathname,int flags);

int open(const char \*pathname, int flags, mode_t mode);

```

De la orden *man* podemos ver lo que hace. Resumiéndolo mucho, abre un archivo con el nombre *pathname* y con unas características que que se hacen explícitas en *flags*. Las flags son *modos de acceso*, O_RDONLY, O_WRONLY o O_RDWR(obligatoria una) y además *flags de creación de archivo*, O_CLOEXEC, O_CREAT, O_DIRECTORY, O_EXECL, O_NOCTTY, O_NOFOLLOW, O_TMPFILE, O_TRUNC.

* O_RDONLY,O_WRONLY,O_RDWR : sólo lectura / sólo escritura / lectura y escritura
* O_CREAT: si el fichero no existe se crea
* O_TMPFILE: crea un archivo temporal. El pathname debe especificar un directorio.
* O_TRUNC : si existe el archivo se borra su contenido(en caso de tener permiso).

En cuanto a los modos indica la máscara de permisos a aplicar sobre el archivo. Hay que tener en cuenta que dicho valor es filtrado con la *umask*, y si la umask es 022 lo que hace es mode & ~umask, quitándole los permisos de umask. Existen constantes de permiso como S_IRUSR que otorga la capacidad de leer el archivo al propietario.

###Llamada al sistema read

``` c
ssize_t read(int fd,void \*buf, size_t count );

```
La llamada trata de leer *count* bytes de *fd* y almacenarlos en el buffer *buf*. La función devuelve el número de bytes que ha podido. El comienzo de la lectura es el punto hasta donde se haya avanzado. Dicho valor lo guarda el descriptor de archivo fd y conforme se lee un byte adelanta una posición el desplazamiento(*offset*). Por tanto, la función adelanta el offset en la cantidad de bytes que haya podido leer. Devuelve cero en caso de estar al final del archivo.

###Llamada al sistema write

``` c
ssize_t write(int fd, const void \*buf, size_t count);
```
En este caso el buffer se utiliza como fuente y el destino es el archivo identificado por *fd*.El número de bytes que trata de copiar es *count*.

###Llamada al sistema lseek

``` c
off_t lseek(int fd, off_t offset, int whence);
```
Esta llamada al sistema permite modificar el *offset* actual de fd. Para ello indicamos la cantidad de bytes con *offset*, a partir de la posición indicada por *whence*. Los posibles valos de *whence* son SEEK_SET, posición absoluta, SEEK_CUR, posición apartir del *offset* actual, o SEEK_END, a partir del final del fichero.

Al usar la orden y avanzar a una posición que esté mas lejos que el final del fichero, e insertar datos, creamos agujeros. Por lo tanto, en nuestro fichero pueden haber dos tipos de regiones, con datos o agujeros. Para buscar un agujero a partir del *offset* que indiquemos usamos la bandera SEEK_HOLE. Mientras que si buscamos encontrar una zona de datos usamos SEEK_DATA.


###Llamada al sistema close

```c
int close(int fd);
```

Cierra el archivo especificado por el descriptor *fd*.


###Programa ejemplo programa1.c

Un ejemplo de uso es *programa1.c*. El programa lee un fichero de texto y va añadiendo su contenido por bloques de 80 bytes, además de insertar una cabecera al inicio de cada bloque.

```c
//Abrimos un archivo con el nombre pasado como argumento por línea de comando y decimos que solo se pueda leer.
if( (fdi=open(argv[1],O_RDONLY))<0){
	printf("\nError %d en open",errno);
	perror("\nError open");
	exit(-1);
}

//Abre el fichero en modo escritura, créandolo en caso de que no exista y borrando los datos si existe. Además indicamos que sea de lectura y escritura para el propietario
if((fdo=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0){
	printf("\nError %d en open",errno);
	perror("\nError open");
	exit(-1);
}


int i=1,tamEncabezado;
char buffer[80];
char encabezado[30];

//Vamos escribiendo en el archivo conforme leemos del de sólo lectura. Al inicio de cada bloque indicamos el número de bloque.
while( (count = read(fdi,buffer,80)) > 0){
	//Escribimos en el archivo
	tamEncabezado = sprintf(encabezado, "Bloque %d\n",i);
	escrito=write(fdo,encabezado,(ssize_t)tamEncabezado);
	escrito=write(fdo,buffer,(ssize_t)count);
	i++;
}
```

Se puede ver una variación del programa en el archivo programa1b.c que incluye la inserción del número de bloques que se han leído al inicio del fichero al finalizar la copia del último bloque.

##Metadatos de un archivo. Estructura stat.

En esta parte vemos la como acceder a la información de un archivo y los campos que tiene la estructura *stat*.

Existen 7 tipos de archivos: regular,directorio, especial de dispositivo de caracteres(usado en módulo 1), especial de dispositivo de bloques( visto en módulo 1), FIFO, enlace simbólico(visto en módulo 1) y socket. Cada archivo guarda sus metadatos en la estructura *stat* y para acceder a ella usamos la llamada al sistema *stat*.

```c
int stat(const char \*pathname, struct stat \*buf);
int fstat(int fd, struct stat \*buf);
int lstat(const char \*pathname, struct stat \*buf);
```
Para obtener la información usamos una variable de tipo *struct stat* donde se almacenan los metadatos. *stat* y *lstat* utilizan la dirección del archivo para obtener la información, la única diferencia es que si el archivo al que nos referimos es un enlace no desreferencia y entonces devuelve la info del enlace.

La estructura almacena entre otra la siguiente info.
```c
struct stat {
  ...
ino_t st_ino;  //el número de inodo que tiene el archivo
mode_t st_mode; // el tipo de archivo que es así como los permisos de acceso
uid_t st_uid; // uid del propietario del achivo
gid_t st_gid; // gid del grupo propietario
off_t st_size; // tamaño en B  del archivo
time_t st_atime; // última hora en que se accedió
time_t st_mtime; // última hora en que se modificó
time_t st_ctime; // última hora en que cambiaron los metadatos
...
};
```

*st_mode* indica el tipo de archivo así como los permisos. Para indicar los valores podemos usar banderas que indican la tripleta *ugo* en total 3 bytes, indicando permisos para *user*,*group* y *other*. Para indicar el tipo de archivo usamos el segundo y tercer byte. En total son 7 B, donde el 2 y 3 indican el tipo de archivo y los tres últimos los permisos.

Para saber el tipo de archivo tenemos macros que nos dicen si es de uno de los 7 tipos, como por ejemplo, S_ISLNK(st_mode) nos dice si es enlace simbólico. Un ejemplo de implementación de la macro se puede ver en programa2.c

```c
#define S_ISREG2(mode) ( ( (mode & 32768) == 32768) ?(1):(0))
```
La macro S_ISREG2(mode) usa 32768 como máscara ya que es la de los archivos regulares(0100000 == regula)
