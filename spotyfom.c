#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "ctmlista2.h"
#include "ctmfila.h"
#include "ctmpilha.h"

struct music *quebraFrase(char *frase);
void playMusic(struct desc_LDE *acervo, int codigo_msc_executada);


int main(void){
	struct desc_LDE *myList = NULL;

	struct desc_queue *playlist_random = NULL;
	struct desc_stack *playlist_pessoal = NULL;
	struct nodo_stack *playlist_pessoal_del = NULL;
	struct nodo_queue *playlist_random_del = NULL;


	int Nsearch, posicao=0;
	char Csearch[256];

	myList = inicializar();
	playlist_random = criaDescQueue();
	playlist_pessoal = criaDescPilha();


    FILE *arquivoEntrada, *arquivoSaida;
	arquivoEntrada = fopen("musicas.txt","r");
	if(arquivoEntrada == NULL){
		printf("não foi possivel abrir o arquivo\n");
		exit(-1);
	}
	
	int tamanhoAcervo;
	fscanf(arquivoEntrada,"%d",&tamanhoAcervo);
	printf("tamanho do acervo sera %d\n",tamanhoAcervo);
	//aloca a struct musica com o tamanho do acervo

	char caractere, frase[256];
	int  n = 0;
	struct nodo *nodo = NULL;
	struct music *musica = NULL;

	while((caractere = fgetc(arquivoEntrada))!= EOF){
		if(caractere != '\n'){ //caractere diferente de \n guarda em frase
			frase[n]=caractere;
			n++;
		}
		else{//encontrou \n
			if(n > 0){
				frase[n]='\0';
				musica = quebraFrase(frase);//carregar acervo
				nodo = criaNodo(musica);
				inserir(myList, nodo, posicao);
				posicao++;
			}
			n=0;
			frase[n]='\0';
		}
	}


	int Opcode;
    do{
        printf("\n1. Execucoes\n2. Criar nova playlist\n3. Buscar\n4. Relatorio\n5. Sair\n");
        scanf("%i",&Opcode);

        switch(Opcode){
            case 1://execuções
            printf("\nescolha uma playlist\n\n1. playlist aleatória\n2. playlist pessoal\n");
			scanf("%i",&Nsearch);

			if(Nsearch == 1){
				if(playlist_random->tamanho == 0)
					printf("\nplaylist vazia, portanto nao pode ser executada.\n");
				else{
					while(playlist_random->head != NULL){
						playlist_random_del = dequeue(playlist_random);
						playMusic(myList, playlist_random_del->info->code);
					}
				}
			}

			else if(Nsearch == 2){
				if(playlist_pessoal->tamanho == 0)
					printf("\nplaylist vazia, portanto nao pode ser executada.\n");
				else{
					while(playlist_pessoal->tamanho != 0){
						playlist_pessoal_del = pop(playlist_pessoal);
						playMusic(myList, playlist_pessoal_del->info->code);
					}
				}
			}

			else
				printf("\nnenhuma das opcoes foram selecionadas.\n");
            break;


			case 2://playlists
			printf("\n\nSua Blibioteca\n\n1. Playlist Aleatória\n2. Playlist Pessoal\n3. Visualizar Playlists\n");
			scanf("%i",&Nsearch);

			if(Nsearch == 1){
				int num, i = 0;
				while(empty_queue(playlist_random) != true)
					dequeue(playlist_random);

				srand(time(NULL));
				printf("informar quantidade de musicas: ");
				scanf("%i",&num);

				while(i < num){
					int random_num = rand()%myList->tamanho;
					enqueue(playlist_random, getRandomNode(myList, random_num));
					i++;
				}
			}

			else if(Nsearch == 2){
				printf("escolha um criterio:\n1. codigo\n2. titulo\n");
				scanf("%i",&Nsearch);

				if(Nsearch == 1){
					printf("informar codigo: ");
					scanf("%i",&Nsearch);
					push(playlist_pessoal, criaNodoPilha(searchByCode(myList, Nsearch)));
				}
				else if(Nsearch == 2){
					printf("informar titulo: ");
					setbuf(stdin, NULL);
					gets(Csearch);
					push(playlist_pessoal, criaNodoPilha(searchByTitle(myList, Csearch)));
				}
				else
					printf("\nnenhuma das opcoes foram selecionadas.\n");
			}

			else if(Nsearch == 3){
				printf("\n\n================================================\nPLAYLIST PESSOAL:\n");
				showStack(playlist_pessoal);
				printf("================================================");
				printf("\n\n\n================================================\nPLAYLIST ALEATORIA:\n");
				showQueue(playlist_random);
				printf("================================================\n");
			}

			else
				printf("\nnenhuma das opcoes foram selecionadas.\n");
			break;


			case 3://buscas
			printf("\nescolha um criterio:\n1. codigo\n2. titulo\n3. artista\n4. todo o acervo\n");
			scanf("%i",&Nsearch);

			if(Nsearch == 1){
				printf("informar codigo: ");
				scanf("%i",&Nsearch);
				searchByCode(myList, Nsearch);
			}

			else if(Nsearch == 2){
				printf("informar titulo: ");
				setbuf(stdin, NULL);
				gets(Csearch);
				searchByTitle(myList, Csearch);
			}

			else if(Nsearch == 3){
				printf("informar artista: ");
				setbuf(stdin, NULL);
				gets(Csearch);
				searchByArtist(myList, Csearch);
			}

			else if(Nsearch == 4){
				imprimir(myList);
			}

			else
				printf("\nnenhuma das opcoes foram selecionadas.\n");
			break;


			case 4:
			arquivoSaida = fopen("relatorio.txt", "w");
			if (arquivoSaida == NULL) {
				printf("Não foi possível criar o arquivo de saída.\n");
				return 1;
			}

			int numeracao = 1;
			struct nodo *aux = myList->LDE;
			while(aux != NULL){
				fprintf(arquivoSaida, "musica %i\n[titulo: %s\nartista: %s\nletra: %s\ncodigo: %i\nexecucoes: %i]\n\n", numeracao, aux->info->title, aux->info->artist, aux->info->lyrics, aux->info->code, aux->info->exe);
				aux = aux->prox;
				numeracao++;
			}

			fclose(arquivoSaida);
			printf("Relatorio criado com sucesso.\n");
			break;


			case 5:
			printf("1. sair\n2. sair e salvar acervo\n\n");
			scanf("%i",&Nsearch);

			if(Nsearch == 1)
				printf("encerrando...\n");

			else if(Nsearch == 2){

				printf("salvando...\nencerrando...\n");
			}

			else
				printf("\nnenhuma das opcoes foram selecionadas.\n");
			break;

			default:
			printf("codigo incorreto!\n");
			break;
        }
    }while(Opcode != 5);

    return 0;
}


struct music *quebraFrase(char *frase){
	int codigo; char artista[256]; char titulo[256]; char letra[256];

	printf("\nloading...\n");
	strcpy(artista,strtok(frase,";"));
	codigo = (int)atoi (strtok(NULL,";"));
	strcpy(titulo,strtok(NULL,";"));
	strcpy(letra,strtok(NULL,";")); 

	struct music *musica = addMusic(codigo, artista, titulo, letra);
	return musica;
}


void playMusic(struct desc_LDE *acervo, int codigo_msc_executada){
	struct nodo *aux = acervo->LDE;

	while(aux->info->code != codigo_msc_executada){
		aux = aux->prox;
	}
	aux->info->exe++;
	return;
}