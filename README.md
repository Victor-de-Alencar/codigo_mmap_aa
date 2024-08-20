# codigo_mmap_aa

    O QUE O PROGRAMA FAZ?

Este programa utiliza páginas de memória virtual do sistema operacional para gerenciar dados em arquivos, permitindo realizar operações de leitura e escrita diretamente na memória.


    PARA RODAR, USE O main.c com:
gcc -o main main.c

./main

Conteúdo:
> Main.c - Arquivo principal que faz a manipulação de memória para leitura e escrita dos arquivos.

> biblia.txt - arquivo que será mapeado na memória.

    DESCRIÇÃO

Primeiramente o programa abre o o arquivo txt e descobre o seu tamanho.
Depois ele descobre o tamanho da página de memória (provavelmente 4096 bytes). 
E então ele mapeia o arquivo em páginas de memória utilizando a função "mmap".
Para testar se tudo funcionou o programa acessa o conteúdo a partir das páginas de memória e calcula quantas páginas e quantos bytes foram utilizados.
E para finalizar ele libera a memória utilizada utilizando a função "munmap".
