#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "ctmlista2.h"
#include "ctmfila.h"
#include "musica.h"

struct nodo_queue *getRandomNode(struct desc_LDE *lista, int rand){
	struct nodo_queue *randomNode = NULL;
	struct nodo *aux = lista->LDE;

	int i = 0;
	while(rand > i){
		i++;
		aux = aux->prox;
	}

	randomNode = criaNodoQueue(aux->info);
	return randomNode;
}



struct desc_LDE *inicializar(void){
    struct desc_LDE *descritor = (struct desc_LDE*) malloc(sizeof(struct desc_LDE));
    descritor->LDE = NULL;
    descritor->tamanho = 0;
    return descritor;
}

struct music *addMusic(int codigo, char artista[], char titulo[], char letra[]){
	struct music *musica = (struct music*)malloc(sizeof(struct music));

	strcpy(musica->artist, artista);
	strcpy(musica->title, titulo);
	strcpy(musica->lyrics, letra);
	musica->exe = 0;
	musica->code = (int) codigo;

	return musica; 
}

struct nodo *criaNodo(struct music *musica){
	struct nodo *novoElemento = (struct nodo*)malloc(sizeof(struct nodo));
	
	novoElemento->info = musica;
	novoElemento->prox = NULL;
	novoElemento->ant = NULL;
	return novoElemento;
}

void inserir(struct desc_LDE *lista, struct nodo *novoElemento, int posicao){
	if((posicao > lista->tamanho)||(posicao < 0)){
		printf("posicao invalida! imprima a lista para ver as posicoes.\n");
		return;
	}

	if(posicao == 0){
		novoElemento->ant = NULL;
		novoElemento->prox = lista->LDE;
        lista->LDE = novoElemento;
        if(lista->tamanho > 0){
            novoElemento->prox->ant = novoElemento;
        }
		lista->tamanho++;
		return;
	}

	int i=0;
	struct nodo *aux = lista->LDE;
	struct nodo *ant;
	while(i < posicao){
		ant=aux;
		aux= aux->prox;
		i++;
	}

	if(aux == NULL){
		novoElemento->ant = aux;
		novoElemento->prox = NULL;
		ant->prox = novoElemento;
		lista->tamanho++;
		return;
	}

	novoElemento->ant = ant;
	novoElemento->prox = aux;
	ant->prox = novoElemento;
	aux->ant = novoElemento;
	lista->tamanho++;
	return;
}

void imprimir(struct desc_LDE *lista){
	struct nodo* aux = lista->LDE;
	int linhas = 0, numeracao = 1;

	if(lista->tamanho == 0)
		printf("vazia!\n");
	else{
		while(aux != NULL){
			printf("\n[titulo: %s\nartista: %s\nletra: %s\ncodigo: %i\nexecucoes: %i]\nmusica %i\n", aux->info->title, aux->info->artist, aux->info->lyrics, aux->info->code, aux->info->exe, numeracao);
			aux = aux->prox;
			linhas++;
			numeracao++;
			if(linhas == 15){
				setbuf(stdin, NULL);
				getchar();
				linhas = 0;
				printf("aperte enter para continuar...\n");
			}
		}
	}
}

struct nodo* remover(struct desc_LDE *lista, int posicao){
	if ((lista->tamanho == 0)||(posicao >= lista->tamanho)){
		printf ("A posicao %i nao existe!\n",posicao);
		return NULL;
	}

	int i=0;
	struct nodo *aux = lista->LDE;
	struct nodo *ant;

	if(posicao == 0){
		lista->LDE = aux->prox;
		if (lista->LDE != NULL) {
        	lista->LDE->ant = NULL;
    	}
		lista->tamanho--;
		free(aux);
		return NULL;
	}
	
	while(i < posicao){
		ant=aux;
	    aux= aux->prox;
	    i++;
	}
	if(aux->prox == NULL){
		ant->prox = NULL;
		lista->tamanho--;
		//free(aux);
		return NULL;
	}
	ant->prox = aux->prox;
	aux->prox->ant = ant;
	lista->tamanho--;
	free(aux);
	return NULL;
}

struct music *searchByCode(struct desc_LDE *lista, int busca){
    int valido = false;
    struct nodo *aux = lista->LDE;
	struct music *playpilha;
    
    while(aux != NULL){
        if(aux->info->code == busca){
            printf("\n[titulo: %s\nartista: %s\nletra: %s\ncodigo: %i\nexecucoes: %i]\n", aux->info->title, aux->info->artist, aux->info->lyrics, aux->info->code, aux->info->exe);
            valido = true;
			playpilha = aux->info;
			return playpilha;
        }
    	aux = aux->prox;
    }
    if(valido == false){
        printf("nenhuma musica com o codigo %i foi encontrada!\n",busca);
    }
}

struct music *searchByTitle(struct desc_LDE *lista, char busca[]){
    int valido = false;
    struct nodo* aux = lista->LDE;
	struct music *playpilha;
    
    while(aux != NULL){
        if(strcasecmp(busca, aux->info->title) == 0){
            printf("\n[titulo: %s\nartista: %s\nletra: %s\ncodigo: %i\nexecucoes: %i]\n", aux->info->title, aux->info->artist, aux->info->lyrics, aux->info->code, aux->info->exe);
            valido = true;
			playpilha = aux->info;
			return playpilha;
        }
    	aux = aux->prox;
    }
    if(valido == false){
        printf("nenhuma musica com o titulo %s foi encontrada!\n",busca);
    }
}

void searchByArtist(struct desc_LDE *lista, char busca[]){
    int valido = false;
    struct nodo* aux = lista->LDE;
    
    while(aux != NULL){
        if(strcasecmp(busca, aux->info->artist) == 0){
            printf("\n[titulo: %s\nartista: %s\nletra: %s\ncodigo: %i\nexecucoes: %i]\n", aux->info->title, aux->info->artist, aux->info->lyrics, aux->info->code, aux->info->exe);
            valido = true;
        }
    	aux = aux->prox;
    }
    if(valido == false){
        printf("nenhuma musica com o artista %s foi encontrada!\n",busca);
    }
}

void deletar(struct desc_LDE *lista){
	struct nodo *aux = lista->LDE;
	struct nodo *temp;

	while(lista->tamanho > 0){
		temp = aux;
 		aux = aux->prox;
 		free(temp);
		lista->tamanho--;
	}
	lista->LDE = NULL;
	printf("lista deletada com sucesso!\n");
}