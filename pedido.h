typedef struct Pedido
{
    char *v;
    int top;
    int size;
} Pedido;

void initializeStack(Pedido *s, int size);
void push(Pedido *s, char ingrediente);
char pop(Pedido *s);
void printStack(Pedido *s);