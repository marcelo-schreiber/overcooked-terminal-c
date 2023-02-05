#include <stdlib.h>
#include <stdio.h>
#include "../include/pedido.h"

void push(Pedido *s, char ingrediente)
{
    Pedido *newOrder;
    newOrder = malloc(sizeof(Pedido));
    newOrder->ingrediente = ingrediente;

    if (s->top == NULL)
    {
        newOrder->next = NULL;
    }
    else
    {
        newOrder->next = s->top; // Make the node as top
    }
    s->top = newOrder; // top always points to the newly created node
}

char pop(Pedido *s)
{
    Pedido *temp;
    char ingrediente;
    if (s->top == NULL)
    {
        return ' ';
    }
    else
    {
        temp = s->top;
        ingrediente = temp->ingrediente;
        s->top = s->top->next;
        free(temp);
    }
    return ingrediente;
}

void popAll(Pedido *s)
{
    Pedido *temp;
    if (s->top == NULL)
    {
        return;
    }
    else
    {
        while (s->top != NULL)
        {
            temp = s->top;
            s->top = s->top->next;
            free(temp);
        }
    }
}

// print stack
void printStack(Pedido *s)
{
    if (s->top == NULL)
    {
        return;
    }
    else
    {
        Pedido *temp;
        temp = s->top;
        while (temp != NULL)
        {
            printf("%c->", temp->ingrediente);
            temp = temp->next;
        }
        printf("\n");
    }
}
