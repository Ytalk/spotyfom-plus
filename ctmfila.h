struct desc_queue{
	struct nodo_queue *head;
	struct nodo_queue *tail;
	int tamanho;
};

struct nodo_queue{
	struct nodo_queue *prox;
	struct music *info;
	struct nodo_queue *ant;
};

struct desc_queue *criaDescQueue(void);
struct nodo_queue *criaNodoQueue(struct music *musica);
void enqueue(struct desc_queue *queue, struct nodo_queue *novoElemento);
struct nodo_queue *dequeue(struct desc_queue *queue);
int empty_queue(struct desc_queue *queue);
int length(struct desc_queue *queue);
void makeNull(struct desc_queue *queue);
struct nodo_queue *head(struct desc_queue *queue);
void showQueue(struct desc_queue *queue);
struct music *criaMusicQueue(int execucoes, int codigo, char artista[], char titulo[], char letra[]);