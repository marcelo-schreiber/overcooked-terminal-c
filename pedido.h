typedef struct pedido
{
    char *v;
    int top;
    int size;
} pedido;

void init(pedido *s, int size);
void push(pedido *s, char ingrediente);
char pop(pedido *s);
void print(pedido *s);