#!/bin/bash

#programa que muestra los archivos modificados en las últimas 24 horas

nombrearchivo="modificados_año_`date +%Y-%d-%T`"
find $HOME -mtime 0  1> $nombrearchivo 2>error.log

