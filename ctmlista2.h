struct nodo{
    struct nodo *prox, *ant;
    struct music *info;
};

struct desc_LDE{
    struct nodo *LDE;
    int tamanho;
};

struct desc_LDE *inicializar(void);
struct music *addMusic(int execucoes, char artista[], char titulo[], char letra[]);
struct nodo *criaNodo(struct music *musica);

void inserir(struct desc_LDE *lista, struct nodo *novoElemento, int posicao);
void imprimir(struct desc_LDE *lista);

struct nodo *remover(struct desc_LDE *lista, int posicao);
void deletar(struct desc_LDE *lista);

struct nodo_queue *getRandomNode(struct desc_LDE *lista, int rand);

struct music *searchByCode(struct desc_LDE *lista, int busca);
struct music *searchByTitle(struct desc_LDE *lista, char busca[]);
void searchByArtist(struct desc_LDE *lista, char busca[]);