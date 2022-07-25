#!/bin/sh
cd "."
qmake -project -o QtTuto.pro 
qmake -makefile -o Makefile "QT += gui widgets" QtTuto.pro 
make clean
make
./QtTuto
