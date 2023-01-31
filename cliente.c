#include <stdlib.h>
#include <stdio.h>
#include "cliente.h"

// queue functions
// initialize queue
void initializeQueue(Cliente *q, int size)
{
    q->head = NULL;
    q->maxSize = size;
    q->tail = NULL;
    q->pedido = NULL;
    q->size = 0;
}

// enqueue
void enqueue(Cliente *q, char *pedido, int tamPedido)
{
    // create new node
    Cliente *newNode = malloc(sizeof(Cliente));
    newNode->pedido = malloc(tamPedido * sizeof(char));
    newNode->pedido = pedido;
    newNode->next = NULL;

    // if queue is empty
    if (q->head == NULL)
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->size++;
}

// dequeue
void dequeue(Cliente *q)
{
    // if queue is empty
    if (q->head == NULL)
    {
        return;
    }
    else
    {
        Cliente *temp = q->head;
        q->head = q->head->next;
        free(temp);
        q->size--;
    }
}

char *peek(Cliente *q)
{
    // if queue is empty
    if (q->head == NULL)
    {
        printf("Fila vazia!");
        return NULL;
    }
    return q->head->pedido;
}

int isFull(Cliente *q)
{
    return q->size == q->maxSize;
}

int isEmpty(Cliente *q)
{
    return q->size == 0;
}

void adicionarPedido(Cliente *q, int pedidoId)
{
    if (isFull(q))
    {
        printf("Fila cheia!");
        return;
    }

    switch (pedidoId)
    {
    case 1:
        enqueue(q, "pHQP", 4); // x-burger
        break;
    case 2:
        enqueue(q, "pHQS", 4); // x-salada
        break;
    case 3:
        enqueue(q, "pHQPFR", 6); // combo 1
        break;
    case 4:
        enqueue(q, "phSPFR", 6); // combo 2
    case 5:
        enqueue(q, "pQPFR", 5); // Vegetariano
        break;
    case 6:
        enqueue(q, "SFR", 3); // Vegano
        break;
    default:
        printf("Pedido invalido!");
        break;
    }
}