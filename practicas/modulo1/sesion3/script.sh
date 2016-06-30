#!/bin/bash

#script para probar la orden nice y renice

if test "$#" -ne 1;then
  echo " Modo de uso: ./script numeroOperaciones" 
  exit 1

fi
ans=100;
inc=0;
for i in `seq 1 $1`;
do
	ans=$(( (3000*5 + 2000/6)*3 ))
	ans=$(( 32199*23 +9))
	ans=$(( ans/9 ))
	inc=$(( inc + 1 ))
done
echo el valor de la variable es $inc
