#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

desc_stack* criaPilha()
{
    desc_stack* stack = (desc_stack *)malloc(sizeof(desc_stack));

    stack->Pilha = NULL;
    stack->tamanho = 0;

    return stack;
}

void push(desc_stack* pilha, Item* novoItem)
{
    if(empty_stack(pilha) == 1)
    {
        pilha->Pilha = novoItem;
        pilha->tamanho++;
    }
    else
    {
        Item *aux = pilha->Pilha;
        novoItem->prox = aux;
        pilha->Pilha = novoItem;
        pilha->tamanho++;
    }
}

Item* pop(desc_stack* pilha)
{
    Item *aux = pilha->Pilha;

    if(empty_stack(pilha) == 1)
    {
        printf("\nErro: pilha esta vazia!\n\n");
    }
    else
    {
        pilha->Pilha = aux->prox;
        pilha->tamanho--;
    }

    return aux;
}

void delete_stack(desc_stack* pilha)
{
    if(empty_stack(pilha) == 1)
    {
        printf("\nErro: a pilha esta vazia!\n\n");
    }
    else
    {
        Item *aux = pilha->Pilha;
        Item *ant;

        while(aux->prox != NULL)
        {
            ant = aux;
            aux = aux->prox;
            pilha->Pilha = aux;
            free(ant);
        }
        free(aux);
        pilha->Pilha = NULL;
        pilha->tamanho = 0;
        printf("\nPilha esvaziada com sucesso!\n\n");
    }
}

void top(desc_stack* pilha)
{
    Item *aux = pilha->Pilha;
    printf("\n\t  --- Primeiro elemento da Pilha ---  \n\n");
    imprimeItem(aux);
}

void imprimePilha(desc_stack* pilha)
{
    if(empty_stack(pilha) == 1)
    {
        printf("\nPilha vazia, insira elementos!\n\n");
    }
    else
    {
        Item *aux = pilha->Pilha;

        while(aux != NULL)
        {
            imprimeItem(aux);
            aux = aux->prox;
        }
    }
}

void destroiPilha(desc_stack* pilha)
{
    Item *aux = pilha->Pilha;
    Item *ant;

    while(aux->prox != NULL)
    {
        ant = aux;
        aux = aux->prox;
        pilha->Pilha = aux;
        free(ant);
    }
    free(aux);
    free(pilha);
    printf("\nPilha destruida com sucesso!\n\n");
}

int empty_stack(desc_stack* pilha)
{
    if(pilha->tamanho == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int lenght(desc_stack* pilha)
{
    return pilha->tamanho;
}