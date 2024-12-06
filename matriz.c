#include "matriz.h"

int **matriz_do_jogo;
int **matriz_visivel;
int linhas, colunas, minas;

void coloca_minas(int linhas, int colunas, int minas) {
    srand(time(NULL));
    int minas_colocadas = 0;
    while (minas_colocadas < minas) {
        int x = rand() % linhas;
        int y = rand() % colunas;
        if (matriz_do_jogo[x][y] != -1) {
            matriz_do_jogo[x][y] = -1;
            minas_colocadas++;
        }
    }
}

void libera_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void atualiza_minas_adjacentes(int x, int y, int linhas, int colunas) {
    int ladoX = -1;
    int ladoY = -1;

    while (ladoX <= 1) {
        ladoY = -1;
        while (ladoY <= 1) {
            if (ladoX == 0 && ladoY == 0) {
                ladoY++;
                continue;
            }
            int novoX = x + ladoX;
            int novoY = y + ladoY;

            if (novoX >= 0 && novoX < linhas && novoY >= 0 && novoY < colunas && matriz_do_jogo[novoX][novoY] != -1) {
                matriz_do_jogo[novoX][novoY]++;
            }
            ladoY++;
        }
        ladoX++;
    }
}

void minas_adjacentes(int linhas) {
    for (int x = 0; x < linhas; x++) {
        for (int y = 0; y < linhas; y++) {
            if (matriz_do_jogo[x][y] == -1) {
                atualiza_minas_adjacentes(x, y, linhas, linhas);
            }
        }
    }
}

int inicia_matriz_do_jogo(int linhas, int colunas, int minas) {
    matriz_do_jogo = (int **)malloc(linhas * sizeof(int *));
    if (matriz_do_jogo == NULL) {
        fprintf(stderr, "Erro na alocação de memória\n");
        exit(1);
    }

    for (int i = 0; i < linhas; i++) {
        matriz_do_jogo[i] = (int *)malloc(colunas * sizeof(int));
        if (matriz_do_jogo[i] == NULL) {
            fprintf(stderr, "Erro na alocação de memória\n");
            exit(1);
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz_do_jogo[i][j] = 0;
        }
    }

    coloca_minas(linhas, colunas, minas);
    minas_adjacentes(linhas);
    return 0;
}

void imprime_matriz(int **matriz, int linhas, int colunas, int revelar) {
    printf("   ");
    for (int j = 0; j < colunas; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < linhas; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < colunas; j++) {
            if (revelar) {
                printf("%3d", matriz[i][j]);
            } else {
                if (matriz[i][j] == -2) {
                    printf("  x");
                } else {
                    printf("%3d", matriz[i][j]);
                }
            }
        }
        printf("\n");
    }
}

void flood_fill(int x, int y, int linhas, int *coordenadas_reveladas) {
    // Verifica limites, se já foi revelado e se é mina
    if (x < 0 || x >= linhas || y < 0 || y >= linhas || 
        matriz_visivel[x][y] != -2 || matriz_do_jogo[x][y] == -1) {
        return;
    }
    //se a posição em que estou verificando é zero
    //verifica se os adjacentes são zeros e recursivamente
    //em profundidade verificando outros zeros
    if (matriz_do_jogo[x][y] == 0) {
        matriz_visivel[x][y] = matriz_do_jogo[x][y];
        (*coordenadas_reveladas)++;
        flood_fill(x-1, y-1, linhas, coordenadas_reveladas); // diagonal superior esquerda
        flood_fill(x-1, y, linhas, coordenadas_reveladas);   // acima
        flood_fill(x-1, y+1, linhas, coordenadas_reveladas); // diagonal superior direita
        flood_fill(x, y-1, linhas, coordenadas_reveladas);   // esquerda
        flood_fill(x, y+1, linhas, coordenadas_reveladas);   // direita
        flood_fill(x+1, y-1, linhas, coordenadas_reveladas); // diagonal inferior esquerda
        flood_fill(x+1, y, linhas, coordenadas_reveladas);   // abaixo
        flood_fill(x+1, y+1, linhas, coordenadas_reveladas); // diagonal inferior direita
    }
}