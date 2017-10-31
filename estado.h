#ifndef ___ESTADO_H___
#define ___ESTADO_H___
#include "cgi.h"
/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/**
\brief O nº de diferentes tipos de inimigos.
*/
#define TIPO 3
/**
\brief O nº máximo de inimigos.
*/
#define MAX_INIMIGOS	(MAX_INIMIGOS1+MAX_INIMIGOS2+MAX_INIMIGOS3)

/**
\brief O nº máximo de inimigos do tipo 1.
*/
#define MAX_INIMIGOS1	6

/**
\brief O nº máximo de inimigos do tipo 2.
*/
#define MAX_INIMIGOS2	4

/**
\brief O nº máximo de inimigos do tipo 3.
*/
#define MAX_INIMIGOS3 	2

/**
\brief O nº máximo de obstáculos.
*/
#define MAX_OBSTACULOS		15

/** \brief O nº máximo de vidas
*/
#define MAX_VIDAS   5

/**
\brief O nº máximo de armadura.
*/
#define MAX_ARMOR	200.0

/**
\brief O nº máximo de baús.
*/
#define MAX_BAUS	3

/**
\brief O nº da range do inimigo.
*/
#define RANGE_INIMIGO	4

/**
\brief Estrutura que armazena uma posição.
*/
typedef struct position {
	int x;
	int y;
} POSITION;

/**
\brief Estrutura que armazena informação dos inimigos.
*/
typedef struct inimigo{
	float vida, ataque;
	POSITION coord;
}INIMIGO;

/**
\brief Estrutura que armazena informação do jogador.
*/
typedef struct jogador{
	float n_vidas, armadura, ataque;
	POSITION coord;
	int stamina, score, beam, ini_derrotados;
} JOGADOR;

/**
\brief Estrutura que armazena informação dos obstáculos.
*/
typedef struct obstaculo{
	POSITION coord;
	int vida;
} OBSTACULO;

/**
\brief Estrutura que armazena informação dos powerpups.
*/
typedef struct powerups{
	POSITION coord;
	int content;
} POWERUPS;

/**
\brief Estrutura que armazena o estado do jogo.
*/
typedef struct estado {
	int num_inimigos1, num_inimigos2, num_inimigos3, num_obstaculos, num_baus;
	int nivel, enc_easter;
	JOGADOR jog;
	POSITION saida;
	POSITION easteregg;
	INIMIGO inimigo[TIPO][MAX_INIMIGOS];
	OBSTACULO obstaculo[MAX_OBSTACULOS];
	POWERUPS bau[MAX_BAUS];

} ESTADO;


#endif
