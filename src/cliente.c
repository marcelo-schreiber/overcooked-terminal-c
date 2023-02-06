#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "../include/cliente.h"
#include "../include/colors.h"

// queue functions
// initialize queue
void initializeQueue(Cliente *q, int size)
{
    q->maxSize = size;
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
}

// enqueue
void enqueue(Cliente *q, char *pedido, int tamPedido)
{
    if (isFull(q) == 1)
        return;

    PedidoAtual *temp = (PedidoAtual *)malloc(sizeof(PedidoAtual));
    temp->ingredientes = (char *)malloc(tamPedido * sizeof(char));
    temp->ingredientes = pedido;
    temp->pedidoId = q->size;
    temp->next = NULL;
    temp->prev = NULL;

    if (q->head == NULL)
    {
        q->head = temp;
        q->tail = temp;
    }
    else
    {
        q->tail->next = temp;
        temp->prev = q->tail;
        q->tail = temp;
    }
    q->size = q->size + 1;
}

// dequeue
void dequeue(Cliente *q)
{
    if (isEmpty(q) == 1)
        return;

    if (q->head == q->tail)
    {
        q->head = NULL;
        q->tail = NULL;
    }
    else
    {
        q->head = q->head->next;
        q->head->prev = NULL;
    }

    q->size = q->size - 1;
}

char *peek(Cliente *q)
{
    if (isEmpty(q) == 1)
        return "Fila vazia!";

    return q->head->ingredientes;
}

int isFull(Cliente *q)
{
    return q->size >= q->maxSize ? 1 : 0;
}

int isEmpty(Cliente *q)
{
    return q->size == 0 ? 1 : 0;
}

void printQueue(Cliente *q)
{
    if (isEmpty(q) == 1)
        return;

    PedidoAtual *temp = q->head;
    printf("╔════════╦════╗\n");
    printf("║ Order  ║ Id ║\n");
    printf("╠════════╬════╣\n");
    while (temp != NULL)
    {
        printf("║ %-6s ║ %-2d ║\n", temp->ingredientes, temp->pedidoId);
        temp = temp->next;
    }
    printf("╚════════╩════╝\n");
}

void adicionarPedido(Cliente *q, int pedidoId)
{
    if (isFull(q) == 1)
        return;

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
        enqueue(q, "pHSPFR", 6); // combo 2
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
