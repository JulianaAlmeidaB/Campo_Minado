# Campo Minado

Este é um jogo de Campo Minado implementado em C, com recursos de log e diferentes níveis de dificuldade.

## Requisitos

- Compilador GCC
- Sistema operacional compatível com C (Linux, MacOS, Windows com MinGW)

## Estrutura do Projeto

```
campo-minado/
│
├── matriz.h       # Definições das funções de manipulação da matriz do jogo
├── matriz.c       # Implementação das funções de manipulação da matriz
├── log.h         # Definições das funções de log
├── log.c         # Implementação das funções de log
└── Juliana_Almeida.c  # Arquivo principal do jogo
```

## Como Compilar

1. Abra o terminal na pasta do projeto
2. Execute o seguinte comando para compilar o programa:

```bash
gcc -o campo_minado Juliana_Almeida.c matriz.c log.c -I.
```

## Como Executar

### Modo Interativo
1. Execute o programa:
   - No Linux/MacOS:
     ```bash
     ./campo_minado
     ```
   - No Windows:
     ```bash
     campo_minado.exe
     ```

### Modo Arquivo de Entrada
É possível executar o jogo usando um arquivo de texto contendo as jogadas:

```bash
./campo_minado < teste.txt
```

O arquivo `teste.txt` deve conter:
- Na primeira linha: o nível do jogo (1, 2 ou 3)
- Nas linhas seguintes: as coordenadas no formato `linha,coluna` (uma por linha)

Exemplo de arquivo `teste.txt`:
```
1
3,4
5,2
1,1
```

## Como Jogar

1. Escolha o nível de dificuldade digitando 1, 2 ou 3
2. Para fazer uma jogada, digite as coordenadas no formato `linha,coluna` (exemplo: `3,4`)
3. Os números revelados indicam quantas minas estão adjacentes àquela célula
4. O jogo termina quando:
   - Você revela uma mina (derrota)
   - Você revela todas as células sem minas (vitória)

### Significado dos Símbolos
- `x`: Célula ainda não revelada
- `0`: Nenhuma mina adjacente
- `1-8`: Número de minas adjacentes
- `-1`: Mina (só aparece quando o jogo termina)

## Recursos Adicionais

- O jogo cria automaticamente um arquivo `log.txt` que registra:
  - Data e hora do início do jogo
  - Estado do campo após cada jogada
  - Resultado final (vitória ou derrota)

## Notas de Implementação

- O jogo utiliza alocação dinâmica de memória para as matrizes
- Implementa o algoritmo flood-fill para revelar automaticamente células vazias adjacentes
- Inclui sistema de logging para acompanhamento das partidas
- Possui validação de entrada para coordenadas inválidas