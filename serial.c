/**
 * @file serial.c
 * @brief Definições estáticas e código das funções de serialização e de-serialização
 *
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "serial.h"
#include "dados.h"
#include "mod_avl_n_dimensional.h"
#include "mod_lista_ligada.h"
#include "mod_tabela_hash.h"


int serialize(TabelaHashPTR tabela, MainTreePt camioes, MainTreePt clientes){
    FILE *file;
    int i, nAdj;
    short int strl;
    MainListPTR *lista = tabela->arraycell;
    LinkedListPTR listaAux = NULL;
    LinkedListPTR adjacencia = NULL;

    file = fopen("dados.sav", "w");
    if( file == NULL ) return 0;
    
    //tamanho do array de hash
    // assim não é preciso fazer re-hash, usa-se este como tamanho inicial
    fwrite(&tabela->totalcells, sizeof(int), 1, file);

    //numero de elementos da tabela de hash
    fwrite(&tabela->nelems, sizeof(int), 1, file);
    for(i=0; i<tabela->totalcells; i++){
        listaAux = lista[i]->elems;
        while( listaAux ){
            strl = strlen(((LocalidadePTR)(listaAux->extdata))->nome);
            fwrite( &strl, sizeof(short int), 1, file );
            //printf("%d", strl);
            fwrite( ((LocalidadePTR)(listaAux->extdata))->nome, sizeof(char), strl, file );
            //printf("%s\n", ((LocalidadePTR)(listaAux->extdata))->nome );
            
            nAdj = ((LocalidadePTR)(listaAux->extdata))->ligacoesida->nelems;
            fwrite( &nAdj, sizeof(int), 1, file );
            adjacencia = ((LocalidadePTR)(listaAux->extdata))->ligacoesida->elems;

            while( adjacencia ){
                strl = strlen( ((LigacoesidaPTR)adjacencia->extdata)->nome );
                fwrite( &strl, sizeof(short int), 1, file );
                
                fwrite( ((LigacoesidaPTR)adjacencia->extdata)->nome, sizeof(char), strl, file );

                fwrite( &((LigacoesidaPTR)adjacencia->extdata)->custo, sizeof(double), 1, file );
                fwrite( &((LigacoesidaPTR)adjacencia->extdata)->distancia, sizeof(double), 1, file );

                adjacencia = adjacencia->prox;
            }
            listaAux = listaAux->prox;
        }
    }

    fwrite( &camioes->nodos, sizeof(unsigned int), 1, file );
    serial_camiao( camioes, file );

    fwrite( &clientes->nodos, sizeof(unsigned int), 1, file );
    serial_cliente( clientes, file );

    

    fclose(file);
    return 1;
}

void serial_clienteRec( TreePt thisTree, FILE *file ){
    ClientePt cliente = NULL;
    LinkedListPTR servico = NULL;
    short int strl;
    int exception = 0;
    if( thisTree != NULL ){
        serial_clienteRec( thisTree->l[0], file);
        
        cliente = (ClientePt)thisTree->node;
        fwrite( &cliente->nif, sizeof(unsigned int), 1, file);
        
        strl = strlen( cliente->nome );
        fwrite( &strl, sizeof(short int), 1, file );
        fwrite( cliente->nome, sizeof(char), strl, file );
        
        strl = strlen( cliente->morada );
        fwrite( &strl, sizeof(short int), 1, file );
        fwrite( cliente->morada, sizeof(char), strl, file );

        if( cliente->servicos != NULL ){
            fwrite( &(cliente->servicos->nelems), sizeof(int), 1, file );
            servico = cliente->servicos->elems;
            while( servico ){
                fwrite( &((ServicoPt)servico->extdata)->custo, sizeof(double), 1, file );
                fwrite( &((ServicoPt)servico->extdata)->peso, sizeof(double), 1, file );

                strl = strlen( ((ServicoPt)servico->extdata)->datahora );
                fwrite( ((ServicoPt)servico->extdata)->datahora, sizeof(char), strl, file );

                strl = strlen( ((ServicoPt)servico->extdata)->camiao );
                fwrite( ((ServicoPt)servico->extdata)->camiao, sizeof(char), strl, file );

                strl = strlen( ((ServicoPt)servico->extdata)->origem );
                fwrite( ((ServicoPt)servico->extdata)->origem, sizeof(char), strl, file );

                strl = strlen( ((ServicoPt)servico->extdata)->carga );
                fwrite( ((ServicoPt)servico->extdata)->carga, sizeof(char), strl, file );

                strl = strlen( ((ServicoPt)servico->extdata)->destino );
                fwrite( ((ServicoPt)servico->extdata)->destino, sizeof(char), strl, file );

                servico = servico->prox;
            }
        }else
            fwrite( &exception, sizeof(int), 1, file );

        serial_clienteRec( thisTree->r[0], file);
    }
}

void serial_cliente(MainTreePt thisMainTree, FILE *file){
    if( thisMainTree != NULL )
        serial_clienteRec( thisMainTree->tree[0], file );
}

void serial_camiaoRec( TreePt thisTree, FILE *file ){
    CamiaoPt camiao = NULL;
    short int strl;
    if( thisTree != NULL ){
        serial_camiaoRec( thisTree->l[0], file);
        
        camiao = (CamiaoPt)thisTree->node;
        fwrite( &camiao->id, sizeof(unsigned int), 1, file);
        fwrite( &camiao->custo, sizeof(double), 1, file );
        fwrite( &camiao->peso, sizeof(double), 1, file );
        
        strl = strlen( camiao->matricula );
        fwrite( &strl, sizeof(short int), 1, file );
        fwrite( camiao->matricula, sizeof(char), strl, file );
        
        strl = strlen( camiao->local );
        fwrite( &strl, sizeof(short int), 1, file );
        fwrite( camiao->local, sizeof(char), strl, file );

        serial_camiaoRec( thisTree->r[0], file);
    }
}

void serial_camiao(MainTreePt thisMainTree, FILE *file){
    if( thisMainTree != NULL )
        serial_camiaoRec( thisMainTree->tree[0], file );
}

char* novaString(unsigned int n){
    return malloc((n+1)*sizeof(char));
}

int deserialize(
        MainTreePt *camioes, int (*comparaCamioes[DIM])(void*,void*),
        MainTreePt *clientes, int (*comparaClientes[DIM])(void*,void*),
        TabelaHashPTR *localidades, int (*comparaLocalidades)(void*,void*), int(*hash_function)(void*,int) ){
    short int strl;
    char *str;
    char *locOrigem;
    int nelem, nelems, tmp;
    int nAdj, nAdjs;
    double dArr[2];

    int teste;
    
    FILE *file;
    fpos_t file_pos;

    apagaTabelaHash(*localidades);
    tree_dispose(camioes);
    tree_dispose(clientes);


    file = fopen("dados.sav", "r");
    if( file == NULL ) return 0;

    fread( &tmp, sizeof(int), 1, file );
    *localidades = criaTabelaHash(hash_function, tmp, comparaLocalidades);

    fread( &nelems, sizeof(int), 1, file );
    fgetpos( file, &file_pos ); //guardar a posição actual

    // inserir as localidades
    for( nelem=0; nelem<nelems; nelem++ ){
        fread( &strl, sizeof(short int), 1, file);
        str = novaString(strl);
        *(str+strl) = '\0';
        fread( str, sizeof(char), strl, file );
        teste = inserelocalidade( *localidades, str ); // localidade inserida
        if( teste != 1 )
            printf(".");

        fread( &nAdjs, sizeof(int), 1, file );
        for( nAdj = 0; nAdj < nAdjs; nAdj++ ){
            fread( &strl, sizeof(short int), 1, file );
            fseek( file, strl*sizeof(char) + 2*sizeof(double) , SEEK_CUR );
        }
    }

    //agora que já tem as localidades, volta atrás e insere as adjacencias
    fsetpos( file, &file_pos );
    for( nelem=0; nelem<nelems; nelem++ ){
        fread( &strl, sizeof(short int), 1, file);
        locOrigem = novaString(strl);
        *(locOrigem+strl) = '\0';
        fread( locOrigem, sizeof(char), strl, file );

        fread( &nAdjs, sizeof(int), 1, file );
        for( nAdj = 0; nAdj < nAdjs; nAdj++ ){
            fread( &strl, sizeof(short int), 1, file );
            free(str);
            str = novaString(strl);
            *(str+strl) = '\0';
            fread( str, sizeof(char), strl, file );
            
            fread( &dArr, sizeof(double), 2, file );
            inserirligacao(*localidades, locOrigem, str, dArr[0], dArr[1]);
        }
    }
    free(locOrigem);
    
    //camiões
    unsigned int id;
    char *matricula=NULL;
    char *local=NULL;
    unsigned int ncamiao, ncamioes;

    *camioes = tree_new( comparaCamioes );

    fread( &ncamioes, sizeof(unsigned int), 1, file );
    for( ncamiao=0; ncamiao<ncamioes; ncamiao++ ){
        fread( &id, sizeof(unsigned int), 1, file);
        fread( &dArr, sizeof(double), 2, file );

        fread( &strl, sizeof(short int), 1, file );
        matricula = novaString(strl);
        *(matricula+strl) = '\0';
        fread( matricula, sizeof(char), strl, file );

        fread( &strl, sizeof(short int), 1, file );
        local = novaString(strl);
        *(local+strl) = '\0';
        fread( local, sizeof(char), strl, file );

        tree_insert( *camioes, camiao_novo(id, matricula, dArr[0], dArr[1], local));
    }

    //clientes
    ClientePt clt=NULL;
    unsigned int nif;
    char *nome;
    char *morada;
    unsigned int ncliente, nclientes;
    int nservico, nservicos;

    char *datahora;
    char *cmatricula;
    char *origem;
    char *carga;
    char *destino;

    *clientes = tree_new( comparaClientes );

    fread( &nclientes, sizeof(unsigned int), 1, file);
    for( ncliente=0; ncliente<nclientes; ncliente++ ){
        fread( &nif, sizeof(unsigned int), 1, file);
        
        fread( &strl, sizeof(short int), 1, file );
        nome = novaString(strl);
        *(nome+strl) = '\0';
        fread( nome, sizeof(char), strl, file );

        fread( &strl, sizeof(short int), 1, file );
        morada = novaString(strl);
        *(morada+strl) = '\0';
        fread( morada, sizeof(char), strl, file );
        
        clt = cliente_novo( nif, nome, morada, criaListaLigada( cliente_comparaServico ));
        tree_insert( *clientes, clt );

        fread( &nservicos, sizeof(int), 1, file );
        for( nservico=0; nservico<nservicos; nservico++){
            fread( &dArr, sizeof(double), 2, file );

            fread( &strl, sizeof(short int), 1, file );
            datahora = novaString(strl);
            *(datahora+strl) = '\0';
            fread( datahora, sizeof(char), strl, file );

            fread( &strl, sizeof(short int), 1, file );
            cmatricula = novaString(strl);
            *(cmatricula+strl) = '\0';
            fread( cmatricula, sizeof(char), strl, file );

            fread( &strl, sizeof(short int), 1, file );
            origem = novaString(strl);
            *(origem+strl) = '\0';
            fread( origem, sizeof(char), strl, file );

            fread( &strl, sizeof(short int), 1, file );
            carga = novaString(strl);
            *(carga+strl) = '\0';
            fread( carga, sizeof(char), strl, file );

            fread( &strl, sizeof(short int), 1, file );
            destino = novaString(strl);
            *(destino+strl) = '\0';
            fread( destino, sizeof(char), strl, file );
            
            cliente_insereServico(*clientes, nif, matricula, dArr[0], dArr[1], origem, carga, destino );

        }
    }

    return 1;
}

