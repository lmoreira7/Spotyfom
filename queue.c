#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

descFila* initializeQueue()
{
    descFila* queue = (descFila *)malloc(sizeof(descFila));
    queue->head = NULL;
    queue->tail = NULL;
    queue->tamanho = 0;

    return queue;
}

void enqueue(descFila* queue, Item* newItem)
{
    if(empty(queue) == 1)
    {
        queue->head = newItem;
        queue->tail = newItem;
        queue->tamanho++;
    }
    else
    {
        Item *aux = queue->head;

        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = newItem;
        newItem->ant = aux;
        queue->tail = newItem;
        queue->tamanho++;
    }
}

Item* dequeue(descFila* queue)
{
    Item *aux = queue->head;

    if(empty(queue) == 1)
    {
        printf("\nErro: fila vazia\n\n");
    }
    else
    {
        queue->head = aux->prox;
        if(queue->tamanho > 1)
        {
            queue->head->ant = NULL;
        }
        queue->tamanho--;
    }
    
    return aux;
}

void showQueue(descFila* queue)
{
    if(empty(queue) == 1)
    {
        printf("\nFila vazia, insira elementos para obter as informacoes!\n\n");
    }
    else
    {
        Item *aux = queue->head;
        
        while(aux != NULL)
        {
            showItem(aux);
            aux = aux->prox;
        }
    }
}

void queueDelete(descFila* queue)
{
    Item *aux = queue->head;
    Item *ant;

    while(aux->prox != NULL)
    {
        ant = aux;
        aux = aux->prox;
        queue->head = aux;
        free(ant);
    }
    free(aux);
    queue->head = NULL;
    queue->tail = NULL;
    queue->tamanho = 0;
    printf("\nFila esvaziada com sucesso!\n\n");
}

void queueDestroy(descFila* queue)
{
    Item *aux = queue->head;
    Item *ant;

    while(aux->prox != NULL)
    {
        ant = aux;
        aux = aux->prox;
        queue->head = aux;
        free(ant);
    }
    free(aux);
    free(queue);
    printf("\nFila destruida!\n\n");
}

void showItem(Item* item)
{
    printf("---------------------------------------------------------\n");
	printf("Nome da musica: %s\n", item->info->titulo);
	printf("Nome do artista: %s\n", item->info->artista);
	printf("Trecho da letra: %s\n", item->info->letra);
	printf("Codigo da musica: %d\n", item->info->codigo);
	printf("Numero de execucoes: %d\n", item->info->execucoes);
	printf("---------------------------------------------------------\n");
}

int empty(descFila* queue)
{
    if(queue->head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int lenghtQueue(descFila* queue)
{
    return queue->tamanho;
}