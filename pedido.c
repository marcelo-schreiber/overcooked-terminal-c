#include <stdlib.h>
#include <stdio.h>
#include "pedido.h"

void init(pedido *s, int size)
{
    s->v = malloc(size * sizeof(char));
    s->size = 0;
    s->top = -1;
}

void push(pedido *s, char ingrediente)
{
    s->size++;
    s->v[s->size - 1] = ingrediente;
    s->top = ingrediente;
}

char pop(pedido *s)
{
    char ingrediente = s->v[s->size - 1];
    s->size--;
    return ingrediente;
}

// print stack
void print(pedido *s)
{
    for (int i = 0; i < s->size; i++)
        printf("%c\t", s->v[i]);
}
