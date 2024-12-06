#include "log.h"

int inicia_log(Log *log) {
    log->arquivo = fopen("log.txt", "w");
    if (log->arquivo == NULL) {
        return 0;
    }

    time_t tempo_atual;
    struct tm *info_tempo;
    char data_hora[50];

    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    strftime(data_hora, 50, "%d/%m/%Y %H:%M:%S", info_tempo);

    fprintf(log->arquivo, "=== Log do Jogo Campo Minado ===\n");
    fprintf(log->arquivo, "Início: %s\n\n", data_hora);

    return 1;
}

void registra_estado(Log *log, int **matriz, int linhas, int colunas, int x, int y) {
    fprintf(log->arquivo, "Estado do Campo:\n");
    fprintf(log->arquivo, "   ");
    
    // Imprime números das colunas
    for (int j = 0; j < colunas; j++) {
        fprintf(log->arquivo, "%3d", j + 1);
    }
    fprintf(log->arquivo, "\n");

    // Imprime matriz
    for (int i = 0; i < linhas; i++) {
        fprintf(log->arquivo, "%2d ", i + 1);
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == -2) {
                fprintf(log->arquivo, "  x");
            } else {
                fprintf(log->arquivo, "%3d", matriz[i][j]);
            }
        }
        fprintf(log->arquivo, "\n");
    }
    fprintf(log->arquivo, "\nCoordenada escolhida: (%d,%d)\n\n", x + 1, y + 1);
}

void fecha_log(Log *log, int **matriz, int linhas, int colunas, int vitoria) {
    fprintf(log->arquivo, "%s\n\n", vitoria ? "Vitória!" : "Game Over!");
    
    fprintf(log->arquivo, "Estado Final do Campo:\n");
    fprintf(log->arquivo, "   ");
    
    // Imprime números das colunas
    for (int j = 0; j < colunas; j++) {
        fprintf(log->arquivo, "%3d", j + 1);
    }
    fprintf(log->arquivo, "\n");

    // Imprime matriz final
    for (int i = 0; i < linhas; i++) {
        fprintf(log->arquivo, "%2d ", i + 1);
        for (int j = 0; j < colunas; j++) {
            fprintf(log->arquivo, "%3d", matriz[i][j]);
        }
        fprintf(log->arquivo, "\n");
    }

    fclose(log->arquivo);
}