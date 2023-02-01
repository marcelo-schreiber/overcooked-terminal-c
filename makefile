parametrosCompilacao=-Wall \
										 -lm \
 										 -pthread
#-Wshadow
nomePrograma=game

all: $(nomePrograma)

$(nomePrograma): main.o cliente.o collision.o mainmenu.o maputils.o moveplayer.o pedido.o
	gcc -o $(nomePrograma) main.o cliente.o collision.o mainmenu.o maputils.o moveplayer.o pedido.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

cliente.o: cliente.c
	gcc -c cliente.c $(parametrosCompilacao)

collision.o: collision.c
	gcc -c collision.c $(parametrosCompilacao)

mainmenu.o: mainmenu.c
	gcc -c mainmenu.c $(parametrosCompilacao)

maputils.o: maputils.c
	gcc -c maputils.c $(parametrosCompilacao)

moveplayer.o: moveplayer.c
	gcc -c moveplayer.c $(parametrosCompilacao)

pedido.o: pedido.c
	gcc -c pedido.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)