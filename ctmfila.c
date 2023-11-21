#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ctmfila.h"
#include "musica.h"

struct desc_queue *criaDescQueue(void){
	struct desc_queue *queue = (struct desc_queue*)malloc(sizeof(struct desc_queue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->tamanho=0;
	return queue;
}

struct nodo_queue *criaNodoQueue(struct music *musica){
	struct nodo_queue *novoNodo = (struct nodo_queue*)malloc(sizeof(struct nodo_queue));
	novoNodo->info = musica;
	novoNodo->prox = NULL;
	return novoNodo;
}

void enqueue(struct desc_queue *queue, struct nodo_queue *novoElemento){
	if(empty_queue(queue) == 1){
		queue->head = novoElemento;
		queue->tail = novoElemento;
	}
	else{
		queue->tail->prox = novoElemento;
		queue->tail = novoElemento;
	}
	queue->tamanho++;
}

struct nodo_queue *dequeue(struct desc_queue *queue){
	struct nodo_queue *aux = queue->head;

	if(queue->tamanho > 0){
		queue->head = queue->head->prox;
		queue->tamanho--;
	}
	return aux;
}

int empty_queue(struct desc_queue *queue){
	if(queue->head == NULL)
		return 1;
		else
		return 0;
}

int length(struct desc_queue *queue){
	return queue->tamanho;
}

void makeNull(struct desc_queue *queue){
		while(empty_queue(queue) == 0){
			free(dequeue(queue));
		}
}

struct nodo_queue* head(struct desc_queue *queue){
	return queue->head;
}

void showQueue(struct desc_queue *queue){
	struct nodo_queue* topo = head(queue);

	if(topo == NULL)
		printf("vazia!\n");

	while(topo != NULL){
		printf("\n[titulo: %s\nartista: %s\nletra: %s\ncodigo: %i\nexecucoes: %i]\n",topo->info->title, topo->info->artist, topo->info->lyrics, topo->info->code, topo->info->exe);
		topo = topo->prox;
	}
}

struct music *criaMusicQueue(int execucoes, int codigo, char artista[], char titulo[], char letra[]){
	struct music *musica = (struct music*)malloc(sizeof(struct music));

	strcpy(musica->artist, artista);
	strcpy(musica->title, titulo);
	strcpy(musica->lyrics, letra);
	musica->exe = execucoes;
	musica->code = codigo;

	return musica; 
}