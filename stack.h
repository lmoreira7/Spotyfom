#include "LDE.h"

typedef struct desc_Pilha desc_stack;

struct desc_Pilha
{
    Item *Pilha;
    int tamanho;
};

desc_stack* criaPilha();
void push(desc_stack* pilha, Item* novoItem);
Item* pop(desc_stack* pilha);
void top(desc_stack* pilha);
void delete_stack(desc_stack* pilha);
void imprimePilha(desc_stack* pilha);
void destroiPilha(desc_stack* pilha);
int empty_stack(desc_stack* pilha);
int lenght(desc_stack* pilha);