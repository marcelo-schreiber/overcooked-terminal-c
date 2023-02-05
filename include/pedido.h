typedef struct stack
{
    char ingrediente;
    struct stack *top;
    int size;

    struct stack *next;
} Pedido;

#define MAX_INGREDIENTES 6

void push(Pedido *s, char ingrediente);
char pop(Pedido *s);
void popAll(Pedido *s);
void printStack(Pedido *s);