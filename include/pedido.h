typedef struct stack
{
    char ingrediente;
    struct stack *top;

    struct stack *next;
} Pedido;

void push(Pedido *s, char ingrediente);
char pop(Pedido *s);
void printStack(Pedido *s);