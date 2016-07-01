#!/bin/sh

ruta=~/Universidad/SO/practicas/modulo1/sesion4;
#reduce el tamaño de la lista
head $ruta/listacores 1> $ruta/aux;
cat $ruta/aux > $ruta/listacores;
rm $ruta/aux;

