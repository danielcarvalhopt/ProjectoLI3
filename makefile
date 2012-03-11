transportes: utils.o arvore.o main.o
	gcc utils.o arvore.o main.o -o transportes

utils.o:
	gcc -c utils.c utils.h -Wall -Wextra

arvore.o:
	gcc -c arvore.c arvore.h -Wall -Wextra

main.o:
	gcc -c main.c -Wall -Wextra

