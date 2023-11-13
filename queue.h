#include "stack.h"

typedef struct desc_queue descFila;

struct desc_queue
{
    Item *head;
    Item *tail;
    int tamanho;
};

descFila* initializeQueue();
void enqueue(descFila* queue, Item* newItem);
Item* dequeue(descFila* queue);
void showQueue(descFila* queue);
void showItem(Item* item);
void queueDelete(descFila* queue);
void queueDestroy(descFila* queue);
int empty(descFila* queue);
int lenghtQueue(descFila* queue);