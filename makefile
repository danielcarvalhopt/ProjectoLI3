transportes: utils.o menu.o arvore.o main.o
	gcc utils.o menu.o arvore.o main.o -o transportes

utils.o:
	gcc -c -g utils.c utils.h -Wall -Wextra

menu.o:
	gcc -c -g menu.c menu.h -Wall -Wextra

arvore.o:
	gcc -c -g arvore.c arvore.h -Wall -Wextra

main.o:
	gcc -c -g main.c -Wall -Wextra
