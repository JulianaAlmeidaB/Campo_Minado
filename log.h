#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

typedef struct {
    FILE *arquivo;
} Log;

/*
* Inicia o arquivo de log com cabeçalho contendo data e hora
* Retorna 1 em caso de sucesso e 0 em caso de erro
*/
int inicia_log(Log *log);

/*
* Registra o estado atual da matriz e a coordenada escolhida pelo jogador
* A matriz é registrada antes da coordenada escolhida
*/
void registra_estado(Log *log, int **matriz, int linhas, int colunas, int x, int y);

/*
* Registra o estado final do jogo e fecha o arquivo
*/
void fecha_log(Log *log, int **matriz, int linhas, int colunas, int vitoria);

#endif