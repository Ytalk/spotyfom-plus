#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ctmpilha.h"

struct desc_stack *criaDescPilha(void){
	struct desc_stack *pilha = (struct desc_stack*)malloc(sizeof(struct desc_stack));
	pilha->top = NULL;
	pilha->tamanho = 0;
	return pilha;
}

struct nodo_stack *criaNodoPilha(struct music *novoElemento){
	struct nodo_stack *novoNodo = (struct nodo_stack*)malloc(sizeof(struct nodo_stack));
	novoNodo->info = novoElemento;
	novoNodo->next = NULL;
	return novoNodo;
}

struct desc_stack *push(struct desc_stack *pilha, struct nodo_stack *novoElemento){
	novoElemento->next = pilha->top;
	pilha->top = novoElemento;
	pilha->tamanho++;
	return pilha;
}

struct nodo_stack *pop(struct desc_stack *pilha){
	struct nodo_stack *aux = pilha->top;
	if(pilha->tamanho > 0){
		pilha->top = pilha->top->next;
		pilha->tamanho--;
	}
	return aux;
}//retornando elemento deletado

int empty_stack(struct desc_stack *pilha){
	if(pilha->top == NULL)
		return 1;
	else
		return 0;
}

int length_stack(struct desc_stack *pilha){
	return pilha->tamanho;
}

/*void makeNull(struct desc_stack *pilha){
		while(empty_stack(pilha) == 0){
			free(pop(pilha));
		}
}*/

struct nodo_stack *top(struct desc_stack *pilha){
	return pilha->top;
}

void showStack(struct desc_stack *pilha){
	struct nodo_stack *topo = top(pilha);
	
	if(topo == NULL)
		printf("vazia!\n");

	while(topo != NULL){
		printf("\n[titulo: %s\nartista: %s\nletra: %s\ncodigo: %i\nexecucoes: %i]\n",topo->info->title, topo->info->artist, topo->info->lyrics, topo->info->code, topo->info->exe);
		topo = topo->next;
	}
}

struct music *addMusicStack(int execucoes, int codigo, char artista[], char titulo[], char letra[]){
	struct music *musica = (struct music*)malloc(sizeof(struct music));

	strcpy(musica->artist, artista);
	strcpy(musica->title, titulo);
	strcpy(musica->lyrics, letra);
	musica->exe = execucoes;
	musica->code = codigo;

	return musica; 
}