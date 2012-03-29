#!/bin/bash

# limpar ficheiros antigos
find . -name "*.gch" -delete
find . -name "*.o" -delete
find . -name "transportes" -delete
find . -name "*.out" -delete

# gerar tags para o projeto
ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .

# limpar o terminal e compilar o projecto
clear
make
