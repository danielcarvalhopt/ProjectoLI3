transportes: utils.o menu.o input.o mod_avl_n_dimensional.o mod_lista_ligada.o dados.o main.o
	gcc utils.o menu.o input.o mod_avl_n_dimensional.o mod_lista_ligada.o dados.o main.o -o transportes

dados.o:
	gcc -c -g dados.c dados.h -Wall -Wextra

utils.o:
	gcc -c -g utils.c utils.h -Wall -Wextra

input.o:
	gcc -c -g input.c input.h -Wall -Wextra

menu.o:
	gcc -c -g menu.c menu.h -Wall -Wextra

mod_lista_ligada.o:
	gcc -c -g mod_lista_ligada.c mod_lista_ligada.h -Wall -Wextra

mod_avl_n_dimensional.o:
	gcc -c -g mod_avl_n_dimensional.c mod_avl_n_dimensional.h -Wall -Wextra

main.o:
	gcc -c -g main.c -Wall -Wextra
