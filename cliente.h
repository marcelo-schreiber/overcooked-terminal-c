
typedef struct Cliente
{
    char *pedido;
    int maxSize;
    int size;
    struct Cliente *head;
    struct Cliente *tail;

    struct Cliente *next;
} Cliente;

void initializeQueue(Cliente *q, int size);
void enqueue(Cliente *q, char *pedido, int tamPedido);
int isEmpty(Cliente *q);
int isFull(Cliente *q);
char *peek(Cliente *q);
void dequeue(Cliente *q);
void adicionarPedido(Cliente *q, int pedidoId);