#Módulo 1. Sesión 3. Monitorización del sistema

##1. Control y gestión de CPU


###a)Orden *uptime*

Para conocer el tiempo que lleva el SO en ejecución, el número de usuarios, y la carga en los últimos 1,5 y 15 minutos.

![](imgs/uptime.png)

Ahí se puede ver que hay **2 usuarios conectados**, lleva funcionando **3 horas 15 minutos**, y la **carga** es **0.04,0.06 y 0.06** siendo la de los últimos 15 minutos 0.06.

###b)Orden time

Indica la cantidad de tiempo que ha necesitado un programa para finalizar. Mostrando tiempo total(real), tiempo de ejecución en modo usuario(user) y tiempo de ejecución en modo kernel(sys). La suma de las ejecuciones es menor o igual que el real debido al *tiempo en espera*.

![](imgs/time.png)

###c)Orden nice y renice

Orden nice. Permite asignar una prioridad a un archivo que queremos ejecutar. Los valores de \[0,19\] son los que pueden usar los usuarios, mientras que si es \[-19,-1\](negativos) sólo puede asignarlos el usuario *root*. Por defecto es 10.

Podemos ver las prioridades de los programas con la utilidad *ps*. La opción -o sirve para indicar la información de los procesos que deseamos monitorizar.

Un ejemplo de cómo se puede adelantar la ejecución de un programa frente a otro que había entrado en el sistema antes se muestra en la siguiente imagen

![](imgs/nice.png)

Para verlo de forma experimental, calculamos los tiempos con la orden time de cada procedimiento. Podiendo ver que el segundo lanzado adelanta al primero, y el tercero debe de esperar a la finalización de los otros dos.

![](imgs/nice2.png)


###d)Orden pstree

Utilidad para ver el árbol de procesos en ejecución en un instante dado.

###e)Orden ps

Sirve para mostrar los procesos que se están ejecujando en un instante. Uno de las formas mas usadas es 

```bash
ps aux
```





