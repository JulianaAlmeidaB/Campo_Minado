#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Definicao de matrizes globais utilizadas no codigo,sao usadas "matriz_do_jogo" para derterminar a matriz criada para o campo.
* Matriz global "matriz_visivel" eh a matriz que sera visivel ao jogador e simula o jogo.
*/
extern int **matriz_do_jogo;
extern int **matriz_visivel;
extern int linhas, colunas, minas;

#define MAX_LINHAS 30
#define MAX_COLUNAS 30
/*
* Função para colocar minas na matriz do jogo,utiliza a funcao rand() que determina numeros em locais aleatorios do campo minado.
* O if verifica se na coordenada ja tem uma mina,alocando-a dependendo do caso e ao final incrementa o contador das minas colocadas.
* Funcao verifica os locais "x,y"
*/
void coloca_minas(int linhas, int colunas, int minas);
/*
* Funcao libera_matriz: libera a memoria alocada dinamicante para a
* matriz do jogo e nesse caso,percorre cada linha da matriz e libera a memoria indivualmente.
*/
void libera_matriz(int **matriz, int linhas);
/* 
* Função para contar e atualizar as minas adjacentes ao redor de minas especificas selecionadas.
* A funcao indica as minas proximas e percorre os lados.
* Como a matriz eh bidimensonal,utilizo ladox,ladoy para representar os pontos da grade.
* Os lados sao reiniciados e de acordo com as minas alocadas ele calcula a posicao que ficara os numeros.
* A funcao verifica se nao ha mina e incrementa ao lado de acordo com o resultado da funcao rand(),que determina isso.
*/
void atualiza_minas_adjacentes(int x, int y, int linhas, int colunas);
/* 
* A funcao percorre a matriz e quando encontra "-1"(mina),chama a funcao "atualiza_minas_adjacentes" para realizar a implementacao das numeracoes.
*/
void minas_adjacentes(int linhas);
/* Inicializa a matriz do jogo e aloca memória primeiramente.
*  Inicializa as células do jogo,linha e coluna como 0 e chama a funcao coloca_minas para colocar minas aleatoriamente.
*  Chama a funcao "minas_adjacentes" para calcular as minas adjacentes e iniciar a matriz visivel do jogo.
*  Inicia a matriz que sera criada com base no numero de linhas e colunas fornecidas pelo usuario.
*/
int inicia_matriz_do_jogo(int linhas, int colunas, int minas);
/*
* A funcao verifica se a coordenada inserida eh valida e verifica as coordenadas inseridas.
* Imprime a matriz com as coorenadas reveladas ou com as minas colocadas.
*/
void imprime_matriz(int **matriz, int linhas, int colunas, int revelar);
/*
* Função recursiva flood_fill, revela automaticamente todas as células com valor 0 
* conectadas à posição inicial (x,y). A revelação ocorre apenas para células não reveladas 
* anteriormente e que contenham valor 0, parando ao encontrar células com outros valores 
* ou limites do tabuleiro.
*/
void flood_fill(int x, int y, int linhas, int *coordenadas_reveladas);
#endif