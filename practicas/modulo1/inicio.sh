#!/bin/bash
#script ejecución entorno de prácticas
cp ~/Descargas/Fedora14-x86-root_fs.gz /tmp/
cp ~/Descargas/kernel32-3.0.4  /tmp/
gzip -d /tmp/Fedora14-x86-root_fs.gz 
cd /tmp/
chmod +x kernel32-3.0.4 Fedora14-x86-root_fs
./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
