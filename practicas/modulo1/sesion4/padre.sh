#!/bin/bash

#para saber qué proceso lanza el ejecutable.

nombrearchivo="padre-`date +%Y-%j-%T`"
ps -o user,pid,ppid,comm -p $$,$PPID > $nombrearchivo
echo Mi pid = $$ y mi padre $PPID >> $nombrearchivo
