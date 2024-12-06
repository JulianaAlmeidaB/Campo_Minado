#include <string.h>
#include "matriz.h"
#include "log.h"

#define NIVEL_FACIL 1
#define NIVEL_MEDIO 2
#define NIVEL_DIFICIL 3

#define MINA -1

typedef struct
{
	int linhas;
	int colunas;
	int minas;
} TConfigIncial;

TConfigIncial obter_configuracao_nivel(int nivel)
{
	TConfigIncial config = {0, 0, 0.15};

	switch (nivel)
	{
	case 1:
		config.linhas = 10;
		config.colunas = 10;
		config.minas = 15;
		break;
	case 2:
		config.linhas = 20;
		config.colunas = 20;
		config.minas = 60;
		break;
	case 3:
		config.linhas = MAX_LINHAS;
		config.colunas = MAX_COLUNAS;
		config.minas = 135;
		break;
	}
	return config;
}

/*
 * Função para ler o nível em que vai ser jogado o campo minado
 */
int ler_nivel()
{
	int nivel;
	printf("Escolha o nível do jogo:\n");
	printf("[1] - Fácil (10x10)\n");
	printf("[2] - Médio (20x20)\n");
	printf("[3] - Difícil (%dx%d)\n", MAX_LINHAS, MAX_COLUNAS);

	scanf("%d", &nivel);

	if (nivel >= NIVEL_FACIL && nivel <= NIVEL_DIFICIL)
	{
		return nivel;
	}

	printf("Nível inválido. Escolha 1, 2 ou 3.\n");
	return NIVEL_FACIL;
}

/*
 * Na função jogo_inicia é alocado a matriz visível ao usuário.
 * Lê as coordenadas enquanto o jogo está em andamento,
 * verifica se a função já teve a coordenada revelada
 * Verifica se o jogador ganhou a partida,
 * verifica se o jogador perdeu a partida
 * ao final libera as matrizes alocadas dinamicamente.
 */
void jogo_inicia()
{
	Log log;
	if (!inicia_log(&log))
	{
		fprintf(stderr, "Erro ao criar arquivo de log\n");
		exit(1);
	}

	matriz_visivel = malloc(linhas * sizeof(int *));
	if (matriz_visivel == NULL)
	{
		fprintf(stderr, "Erro na alocação de memória\n");
		exit(1);
	}

	for (int i = 0; i < linhas; i++)
	{
		matriz_visivel[i] = malloc(colunas * sizeof(int));
		if (matriz_visivel[i] == NULL)
		{
			fprintf(stderr, "Erro na alocação de memória\n");
			exit(1);
		}
		for (int j = 0; j < colunas; j++)
		{
			matriz_visivel[i][j] = -2;
		}
	}

	int coordenadas_reveladas = 0;
	int total = linhas * colunas - minas;

	while (1)
	{
		printf("\nCampo Minado:\n");
		imprime_matriz(matriz_visivel, linhas, colunas, 0);

		int x, y;
		printf("Digite coordenada(linha,coluna): ");

		if (scanf("%d,%d", &x, &y) != 2)
		{
			printf("insira dois números separados por vírgula.\n");
			continue;
		}

		x--;
		y--;

		if (x < 0 || x >= linhas || y < 0 || y >= colunas)
		{
			printf("essas coordenadas sao invalidas\n");
			continue;
		}

		if (matriz_visivel[x][y] != -2)
		{
			printf("Coordenada já revelada,escolha outra\n");
			continue;
		}

		registra_estado(&log, matriz_visivel, linhas, colunas, x, y);

		if (matriz_do_jogo[x][y] == MINA)
		{
			fprintf(log.arquivo, "=== Fim do Jogo ===\n");
			printf("game Over\n");
			printf("Matriz Completa:\n");
			imprime_matriz(matriz_do_jogo, linhas, colunas, 1);
			fecha_log(&log, matriz_do_jogo, linhas, colunas, 0);
			break;
		}

		if (matriz_do_jogo[x][y] == 0)
		{
			flood_fill(x, y, linhas, &coordenadas_reveladas);
		}
		else
		{
			matriz_visivel[x][y] = matriz_do_jogo[x][y];
			coordenadas_reveladas++;
		}

		if (coordenadas_reveladas >= total)
		{
			printf("parabens,vc eh fera\n");
			printf("matriz Completa:\n");
			imprime_matriz(matriz_do_jogo, linhas, colunas, 1);
			fecha_log(&log, matriz_do_jogo, linhas, colunas, 1);
			break;
		}
	}

	libera_matriz(matriz_do_jogo, linhas);
	libera_matriz(matriz_visivel, linhas);
}
int main()
{
	int nivel = ler_nivel();
	TConfigIncial config = obter_configuracao_nivel(nivel);

	linhas = config.linhas;
	colunas = config.colunas;
	minas = config.minas;

	inicia_matriz_do_jogo(linhas, colunas, minas);
	jogo_inicia();

	return 0;
}