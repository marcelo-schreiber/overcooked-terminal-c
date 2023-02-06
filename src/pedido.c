#include <stdlib.h>
#include <stdio.h>
#include "../include/pedido.h"
#include "../include/colors.h"

void initializeStack(Pedido *s)
{
    s->top = NULL;
    s->size = 0;
}

void push(Pedido *s, char ingrediente)
{
    Pedido *newOrder;
    newOrder = malloc(sizeof(Pedido));
    newOrder->ingrediente = ingrediente;

    if (s->size > MAX_INGREDIENTES)
        return;

    s->size = s->size + 1;

    if (s->top == NULL)
        newOrder->next = NULL;
    else
        newOrder->next = s->top; // Make the node as top

    s->top = newOrder; // top always points to the newly created node
}

char pop(Pedido *s)
{
    Pedido *temp;
    char ingrediente;
    if (s->top == NULL)
        return ' ';

    temp = s->top;
    ingrediente = temp->ingrediente;
    s->top = s->top->next;
    s->size = s->size - 1;
    free(temp);

    return ingrediente;
}

void popAll(Pedido *s)
{
    Pedido *temp;
    if (s->top == NULL)
        return;

    while (s->top != NULL)
    {
        temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
}

// print stack
void printStack(Pedido *s)
{
    if (s->top == NULL)
        return;

    Pedido *temp;
    temp = s->top;
    printf("\n");
    while (temp != NULL)
    {
        printf("    %c\n", temp->ingrediente);
        temp = temp->next;
    }
    darkGray();
    printf("\\______/"); // plate
    reset();
}
