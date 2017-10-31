#ifndef __PROTOTIPOS_H__
#define __PROTOTIPOS_H__
#include "estado.h"
#include "cgi.h"
/**
@file prototipos.h
Ficheiro com todos os prototipos usados no jogo.
*/

/**
* Prototipos
*/
int procura_obscatulos(ESTADO e, int coordx, int coordy);
int tem_bau(ESTADO e, int x, int y);
ESTADO mover_inimigo_ranged(ESTADO e, int i, int tipo);
int ataque_dos_inimigos_ranged(ESTADO *e, int i, int tipo);
int posicao_igual(POSITION coords, int x, int y);
void print_ataca_beam(ESTADO e);
void escreve_pontos(FILE *score, char *filename, int myscore);
void ataca_inimigo_beam(ESTADO *e, int dx, int dy);
int ataque_dos_inimigos(ESTADO *e, int i, int tipo);
void ataca_o_inimigo(ESTADO *e, int x, int y, int dano);
ESTADO movimentos_inimigos(ESTADO e);
void morreu_jogador(ESTADO e);
ESTADO ler_ficheiro(FILE *state, char *filename);
int tem_obstaculo(ESTADO e, int x, int y);
void escreve_ficheiro(FILE *state, ESTADO e, char *filename);
void print_easteregg(ESTADO e, int id_easter);
ESTADO enc_easteregg(ESTADO e);
ESTADO inicializar_easteregg(ESTADO e);
char *estado2str(ESTADO e);
ESTADO str2estado(char *argumentos);
void imprime_movimentos(ESTADO e);
int mov_valido(ESTADO e, int x, int y);
int posicao_ocupada(ESTADO e, int x, int y);
int posicao_valida(int x, int y);
void matriz_mapa_casa(ESTADO *e, int x, int y, int n);
void matriz_mapa(ESTADO *e);

/**
Matriz com as distancias das casa do mapa em relacao ao jogador.
*/
extern int matriz[TAM][TAM];

/**
\brief Estrutura usada para tornar os movimentos dos inimigos mais inteligentes(atraves de um qsort).
* x - Coordenada x
* y - Coordenada y
* dist - distancia em relacao ao jogador
* rnd - valor de desempate, gerado pelo random()
*/
typedef struct pos_dist {
	int x;
	int y;
	int dist;
	int rnd;
} POS_DIST;

/**
\brief Estrutura usada para tornar os movimentos dos inimigos mais inteligentes(atraves de um qsort).
A diferenca desta é que foi feita para inimigos que atacam de longe.
* x - Coordenada x
* y - Coordenada y
* dist - distancia em relacao ao jogador
* igual - 1 se tiver alguma coordenada igual ao jogador, 0 se nao tiver
* obstaculo - 1 se tiver obstaculo entre o jogador e o inimigo, 0 se nao tiver
* rnd - valor de desempate, gerado pelo random()
*/
typedef struct pos_dist2 {
	int x;
	int y;
	int dist;
  int igual;
  int obstaculo;
	int rnd;
} POS_DIST2;

#endif
