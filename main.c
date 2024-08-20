#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Abrir o arquivo
    int arquivo = open("./biblia.txt", O_RDONLY); // Se quiser testar com um arquivo diferente terá que mudar o nome do txt nesta linha de código
    if (arquivo == -1) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Obter o tamanho do arquivo
    struct stat info_arquivo;
    if (fstat(arquivo, &info_arquivo) == -1) {
        perror("Erro ao obter tamanho do arquivo");
        close(arquivo);
        exit(EXIT_FAILURE);
    }

    // Obter o tamanho da página do sistema
    long tamanho_pagina = sysconf(_SC_PAGESIZE);
    if (tamanho_pagina == -1) {
        perror("Erro ao obter tamanho da página");
        close(arquivo);
        exit(EXIT_FAILURE);
    }

    // Mapear o arquivo para a memória
    void *mapa_memoria = mmap(NULL, info_arquivo.st_size, PROT_READ, MAP_PRIVATE, arquivo, 0);
    if (mapa_memoria == MAP_FAILED) {
        perror("Erro ao mapear arquivo na memória");
        close(arquivo);
        exit(EXIT_FAILURE);
    }

    // Acessar os dados do arquivo através do mapeamento de memória
    printf("Conteúdo do arquivo mapeado na memória:\n%.*s\n", (int)info_arquivo.st_size, (char *)mapa_memoria);

    // Calcular o número de páginas utilizadas
    long paginas_utilizadas = (info_arquivo.st_size + tamanho_pagina - 1) / tamanho_pagina;  // Arredondar para cima
    printf("Número de páginas de memória utilizadas: %ld\n", paginas_utilizadas);
    printf("Tamanho do arquivo: %lld bytes\n", (long long)info_arquivo.st_size);

    // Desmapear o arquivo da memória
    if (munmap(mapa_memoria, info_arquivo.st_size) == -1) {
        perror("Erro ao desmapear a memória");
    }

    // Fechar o descritor de arquivo
    close(arquivo);

    return 0;
}
