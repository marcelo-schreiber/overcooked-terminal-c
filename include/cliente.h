
typedef struct pedidoAtual
{
    char *ingredientes;
    struct pedidoAtual *next;
    struct pedidoAtual *prev;
} PedidoAtual;

typedef struct Cliente
{
    int maxSize;
    int size;

    PedidoAtual *head;
    PedidoAtual *tail;
} Cliente;

void printQueue(Cliente *q);
void initializeQueue(Cliente *q, int size);
void enqueue(Cliente *q, char *pedido, int tamPedido);
int isEmpty(Cliente *q);
int isFull(Cliente *q);
char *peek(Cliente *q);
void dequeue(Cliente *q);
void adicionarPedido(Cliente *q, int pedidoId);