#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LDE.h"

Descritor* criaDesc()
{
	Descritor* list = (Descritor *)malloc(sizeof(Descritor));

	list->inicio = NULL;
	list->fim = NULL;
	list->tamanho = 0;
	
	return list;
}

Music* criaMusica(char *title, char *art, char *let, int cod, int exec)
{
	Music* newMusica = (Music *)malloc(sizeof(Music));

	strcpy(newMusica->titulo, title);
	strcpy(newMusica->artista, art);
	strcpy(newMusica->letra, let);
	newMusica->codigo = cod;
	newMusica->execucoes = exec;

	return newMusica;
}

Music* loadDataBase()
{
	FILE* arquivoEntrada;
	arquivoEntrada = fopen("musicas.txt", "r");
	if(arquivoEntrada == NULL)
	{
		printf("\nErro: nao foi possivel acessar o arquivo!\n\n");
	}
	int tamanhoAcervo;
	fscanf(arquivoEntrada, "%d", &tamanhoAcervo);

	Music* acervo = (Music *)malloc(tamanhoAcervo * sizeof(Music));

	char caractere;
	char frase[256];
	int n = 0, i = 1;

	while((caractere = fgetc(arquivoEntrada)) != EOF)
	{
		if(caractere != '\n')
		{
			frase[n] = caractere;
			n++;
		}
		else
		{
			if(n > 0)
			{
				frase[n] = '\0';
				quebraFrase(acervo, frase, i);
				i++;
			}

			n = 0;
			frase[n] = '\0';
		}
	}

	return acervo;
}

Item* criaItem(Music* infoMusica)
{
	Item* newItem = (Item *)malloc(sizeof(Item));
	
	newItem->info = infoMusica;
	newItem->prox = NULL;
	newItem->ant = NULL;
	
	return newItem;
}

Descritor* initialize_acervo(Music* acervo, int tamanhoAcervo)
{
	Descritor* list = NULL;
	Music* copyAcervo = NULL;
	Item* newNodo = NULL;
	int i = 1;

	list = criaDesc();
	while(i <= tamanhoAcervo)
	{
		modify_String(acervo[i].artista);
		copyAcervo = criaMusica(acervo[i].titulo, acervo[i].artista, acervo[i].letra, acervo[i].codigo, acervo[i].execucoes);
		newNodo = criaItem(copyAcervo);
		insereLista(list, newNodo, tamanhoAcervo);
		copyAcervo = NULL;
		newNodo = NULL;
		i++;
	}

	return list;
}

void get_title(Descritor* lista, char *title, int tamanhoAcervo)
{
	Item *aux = lista->inicio;
	int verificador = 0, i = 1;
	char *sub_string;

	while(i <= tamanhoAcervo)
	{
		sub_string = strstr(aux->info->titulo, title);
		if(sub_string != NULL)
		{
			imprimeItem(aux);
			verificador = 1;
		}
		sub_string = NULL;
		aux = aux->prox;
		i++;
	}

	if(verificador == 0)
	{
		printf("\nErro: titulo nao encontrado em seu acervo!\n\n");
	}
	
}

Item* get_cod(Descritor* lista, int cod)
{
	Item *aux = lista->inicio;
	int verificador = 0;

	while(aux != NULL)
	{
		if(cod == aux->info->codigo)
		{
			verificador = 1;
			aux->ant = NULL;
			aux->prox = NULL;
			return aux;
		}

		aux = aux->prox;
	}

	if(verificador == 0)
	{
		return NULL;
	}
}

void get_art(Descritor* lista, char *name, int tamanhoAcervo)
{
	int i = 1;
	Item* aux = lista->inicio;
	int verificador = 0;
	char *sub_string;

	printf("\n");
	printf("\t\t\t\t	       --- Voce pesquisou por [%s] no acervo ---	\n\n", name);
	while(i <= tamanhoAcervo)
	{
		sub_string = strstr(aux->info->artista, name);
		if(sub_string != NULL)
		{
			imprimeItem(aux);
			verificador = 1;
		}
		sub_string = NULL;
		aux = aux->prox;
		i++;
	}

	if(verificador == 0)
	{
		printf("\nErro: nao foram encontradas musicas do artista %s no seu acervo!\n\n", name);
	}
}

void quebraFrase(Music* acervo, char *frase, int indice)
{
	strcpy(acervo[indice].artista, strtok(frase, ";"));
	acervo[indice].codigo = atoi(strtok(NULL, ";"));
	strcpy(acervo[indice].titulo, strtok(NULL, ";"));
	strcpy(acervo[indice].letra, strtok(NULL, ";"));
	acervo[indice].execucoes = atoi(strtok(NULL, "\0"));
}

void removeLista(Descritor* lista, int posicao)
{
	if(tamanhoLista(lista) == 0 || posicao > lista->tamanho)
	{
		printf("\nPosicao invalida!\n\n");
	}
	else
	{
		if(posicao == 0)
		{
			Item *aux = lista->inicio;
			lista->inicio = aux->prox;
			if(lista->tamanho > 1)
			{
				aux->prox->ant = NULL;
			}
			free(aux);
			lista->tamanho--;
		}
		else if(posicao == lista->tamanho-1)
		{
			Item *aux = lista->inicio;

			while(aux->prox != NULL)
			{
				aux = aux->prox;
			}
			aux->ant->prox = NULL;
			lista->fim = aux->ant;
			free(aux);
			lista->tamanho--;
		}
		else
		{
			if(posicao < lista->tamanho-1)
			{
				Item *aux = lista->inicio;
				Item *anterior;
				int i = 0;
	
				while(i < posicao)
				{
					anterior = aux;
					aux = aux->prox;
					i++;
				}
	
				anterior->prox = aux->prox;
				aux->prox->ant = anterior;
				free(aux->info);
				free(aux);
				printf("\nElemento removido com sucesso na posicao [%d] da lista!\n\n", posicao);
				lista->tamanho--;
			}
		}
	}
			
}

void insereLista(Descritor* lista, Item* info, int posicao)
{
	if(lista->inicio == NULL)
	{
		lista->inicio = info;
		lista->fim = info;
		lista->tamanho++;
	}
	else
	{
		if(posicao == 0)
		{
			Item *aux = lista->inicio;
			info->prox = aux;
			aux->ant = info;
			lista->inicio = info;
			lista->tamanho++;
		}
		else if(posicao == lista->tamanho || posicao > lista->tamanho)
		{
			Item *aux = lista->inicio;

			while(aux->prox != NULL)
			{
				aux = aux->prox;
			}
			aux->prox = info;
			lista->fim = info;
			info->ant = aux;
			lista->tamanho++;
		}
		else
		{
			Item *aux = lista->inicio;
			Item *anterior;
			int i = 0;
	
			while(i < posicao)
			{
				anterior = aux;
				aux = aux->prox;
				i++;
			}
	
			anterior->prox = info;
			info->prox = aux;
			info->ant = anterior;
			lista->tamanho++;
		}
	}
}

Item* buscaLista(Descritor* lista, int posicao)
{
	if(tamanhoLista(lista) == 0 || posicao > lista->tamanho)
	{
		printf("\nPosicao invalida!\n\n");
		return NULL;
	}
	else
	{
		int i = 0;
		Item *aux = lista->inicio;
			
		while(i < posicao)
		{
			aux = aux->prox;
			i++;
		}
			
		return aux;
	}

	return NULL;
}

void imprimeItem(Item* item)
{
	if(item == NULL)
	{
		printf("\nErro: a musica pesquisada nao esta no seu acervo!\n\n");
	}
	else
	{
		printf("---------------------------------------------------------\n");
		printf("Nome da musica: %s\n", item->info->titulo);
		printf("Nome do artista: %s\n", item->info->artista);
		printf("Trecho da letra: %s\n", item->info->letra);
		printf("Codigo da musica: %d\n", item->info->codigo);
		printf("Numero de execucoes: %d\n", item->info->execucoes);
		printf("---------------------------------------------------------\n");
	}
}

void imprimeLista(Descritor* lista)
{
	Item *aux = lista->inicio;
	
	printf("\n	--- Lista Musical ---	\n\n");
	
	while(aux != NULL)
	{
		imprimeItem(aux);
		aux = aux->prox;
	}
}

void destroiLista(Descritor* lista)
{
	Item *aux = lista->inicio;
	Item *anterior;
	
	while(aux->prox != NULL)
	{
		anterior = aux;
		aux = aux->prox;
		lista->inicio = aux;
		free(anterior->info);
		free(anterior);
	}
	
	free(aux->info);
	free(aux);
	free(lista);
}

int tamanhoLista(Descritor* lista)
{
	return lista->tamanho;
}

void exec_playlist(Music* acervo, Item* infoMusica)
{
	int i = 1;
	
	while(acervo[i].codigo != infoMusica->info->codigo)
	{
		i++;
	}

	acervo[i].execucoes++;
}

void modify_String(char *string)
{
    int i = 0;

    while(string[i] != '\0')
    {
        string[i] = toupper(string[i]);
        i++;
    }

    string[i] = '\0';
}

void Relatorio_Acervo(Music* acervo, int tamanhoAcervo)
{
	FILE* arquivoSaida;
	arquivoSaida = fopen("musicas.txt", "w");

	if(arquivoSaida == NULL)
	{
		printf("\nErro: relatorio nao pode ser criado!\n\n");
	}

	int i = 1;

	fprintf(arquivoSaida, "%d\n", tamanhoAcervo);

	while(i <= tamanhoAcervo)
	{
		fprintf(arquivoSaida, "%s;", acervo[i].artista);
		fprintf(arquivoSaida, "%d;", acervo[i].codigo);
		fprintf(arquivoSaida, "%s;", acervo[i].titulo);
		fprintf(arquivoSaida, "%s;", acervo[i].letra);
		fprintf(arquivoSaida, "%d\n", acervo[i].execucoes);

		i++;
	}
	
}

int lenght_acervo()
{
    int tam = 0;

    FILE* arquivoEntrada;
    arquivoEntrada = fopen("musicas.txt", "r");
    fscanf(arquivoEntrada, "%d", &tam);

    return tam;
}

int index_random()
{
    int index = 0;

    index = rand()%5000;

    return index;
}