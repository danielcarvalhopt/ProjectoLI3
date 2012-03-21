transportes: utils.o menu.o ndavl.o main.o
	gcc utils.o menu.o ndavl.o main.o -o transportes

utils.o:
	gcc -c -g utils.c utils.h -Wall -Wextra

menu.o:
	gcc -c -g menu.c menu.h -Wall -Wextra

ndavl.o:
	gcc -c -g ndavl.c ndavl.h -Wall -Wextra

main.o:
	gcc -c -g main.c -Wall -Wextra
