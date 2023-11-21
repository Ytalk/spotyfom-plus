struct music{
    char title[256];
    char artist[256];
    char lyrics[256];
    int code;
    int exe;
};

struct nodo_stack{
	struct nodo_stack *next;
	struct music *info;
};

struct desc_stack{
	struct nodo_stack *top;
	int tamanho;
};

struct desc_stack *criaDescPilha(void);
struct nodo_stack *criaNodoPilha(struct music *novoElemento);
struct desc_stack *push(struct desc_stack *pilha, struct nodo_stack *novoElemento);
struct nodo_stack *pop(struct desc_stack *pilha);
int empty_stack(struct desc_stack *pilha);
int length_stack(struct desc_stack *pilha);
struct nodo_stack *top(struct desc_stack *pilha);
void showStack(struct desc_stack *pilha);
struct music *addMusicStack(int execucoes, int codigo, char artista[], char titulo[], char letra[]);
