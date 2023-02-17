# Overcooked no terminal
Um clone de overcooked feito para ser jogado no terminal, feito em C.

## Demonstração

![Alt Text](https://cdn.discordapp.com/attachments/685226653764550671/1072509849289621645/2023-02-07_10-27-30.gif)
## Instalação

Tenha certeza de ter *GCC* e *MAKE* (geralmente já vem instalado por padrão em algumas distribuições Linux)

```bash
  git clone https://github.com/marcelo-schreiber/overcooked-terminal-c.git
```

```bash
  cd overcooked-terminal-c && make
```

```bash
  ./overcooked
```
Caso não tenha instalado as bibliotecas necessárias
```bash
  sudo apt update && sudo apt install build-essential
```
Além disso, o ncurses que verifica o tamanho do terminal antes de iniciar
```bash
  sudo apt-get install libncurses5-dev libncursesw5-dev
```

Caso não queira instalar o *ncurses*, o que poderá causar uma interface quebrada quando o terminal estiver pequeno, ao invés de um aviso para redimensioná-lo, clone a branch *no-libs* e siga os mesmo processo:

```bash
  git clone https://github.com/marcelo-schreiber/overcooked-terminal-c.git -b no-libs
```
```bash
  cd overcooked-terminal-c && make
```

```bash
  ./overcooked
```

## Roadmap

- Adicionar concorrência entre os pedidos

- Mover-se nas setas

- Nível de dificuldade


## Licença

[MIT](https://choosealicense.com/licenses/mit/)


## Feedback

Se você tiver algum feedback, por favor nos deixe saber por meio de marcelorissette15@gmail.com

