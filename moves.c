#include "estado.h"
#include "cgi.h"
#include "prototipos.h"
#include <stdlib.h>


#define CASA_INVALIDA  999
#define IGUAL(x1, y1, x2, y2) (x1 == x2 || y1 == y2)
#define CONDICAO_IDEAL  ((pa->dist >= 2 && pa->dist <= RANGE_INIMIGO) && (pb->dist >= 2 && pb->dist <= RANGE_INIMIGO))
#define CONDITION_TO_MOVE		e.num_inimigos2 <= (MAX_INIMIGOS2-2) || (e.num_inimigos2 <= (MAX_INIMIGOS2-1) && e.num_inimigos1 <= (MAX_INIMIGOS1-3))\
														|| e.num_inimigos1 <= (MAX_INIMIGOS1-4) || e.num_inimigos3 <= (MAX_INIMIGOS3-1)

int matriz[TAM][TAM];

/**
@file moves.c
* Ficheiro com funcoes relacionadas com movimentos
*/

/**
\brief Funcao auxiliar que da valores a cada casa em relacao ao jogador
@param e Apontador para o estado atual do jogo
@param x Coordenada x da casa no tabuleiro
@param y Coordenada y da casa no tabuleiro
@param n Valor a ser colocado na casa

* Por cada chamada recursiva desta funcao, 'n' vai incrementando (aumenta a distancia ao jogador)
* Aplica a chamada recursiva, inicialmente, a cada casa que o jogador pode mover-se para, e depois para
* as casas seguintes, ate encontrar obstaculos (movimentos impossiveis)
*/
void matriz_mapa_casa(ESTADO *e, int x, int y, int n){
  int dx, dy, novo_x, novo_y;

  matriz[y][x] = n;

  for (dy = -1; dy < 2; dy++){
    for (dx = -1; dx < 2; dx++){
      novo_x = x + dx;
      novo_y = y + dy;

      if(matriz[novo_y][novo_x] > n && posicao_valida(novo_x, novo_y)
                        && !tem_obstaculo(*e, novo_x, novo_y)){
        matriz[novo_y][novo_x] = n+1;
        matriz_mapa_casa(e, novo_x, novo_y, n+1);
      }
    }
  }
}

/**
\brief Funcao que atribui a cada casa um valor de distancia em relacao ao jogador
@param e Apontador para o estado atual do jogo
*/
void matriz_mapa(ESTADO *e){
  int l, c;

  for (l = 0; l < TAM; l++)
    for (c = 0; c < TAM; c++) /*Resetar o array FAZER DEFINE*/
      matriz[l][c] = CASA_INVALIDA;

  matriz_mapa_casa(e, e->jog.coord.x, e->jog.coord.y, 0);
}

/**
\brief Metodo de organizacao usado pelo qsort, para os movimentos de inimigos que atacam de longe
@returns Posicao no array a ser sorteado
* Se duas casas vizinhas do inimigo tiver, apenas:
* A mesma distancia ao jogador, tiverem uma coordenada igual ao jogador, tiverem as duas
* um obstaculo entre ele e o jogador e tiver dentro do raio ideal para atacar, entao gera um nº aleatorio para "desempatar".
* A mesma distancia ao jogador, tiverem uma coordenada igual ao jogador e tiverem as duas e
* tiver dentro do raio ideal para atacar, entao o que nao tiver obstaculo fica primeiro que o outro.
* A mesma distancia ao jogado e tiver dentro do raio ideal para atacar,
* entao o que tiver uma coordenada igual ao jogador fica primeiro que o outro.
* A mesma distancia ao jogador, entao o que estiver no raio ideal fica primeiro que o outro.
*
* Senao o que tiver menor distancia fica primeiro que o outro
*/
int comparator2(const void * a, const void *b) {
	POS_DIST2 *pa = (POS_DIST2 *) a;
	POS_DIST2 *pb = (POS_DIST2 *) b;
	if (pa->dist == pb->dist && (pa->igual && pb->igual)
  && (pa->obstaculo && pb->obstaculo) && CONDICAO_IDEAL)
		return ((pa->rnd - pb->rnd) % 11);
  if (pa->dist == pb->dist && CONDICAO_IDEAL && (pa->igual && pb->igual))
      return (pa->obstaculo - pb->obstaculo);
  if (pa->dist == pb->dist && CONDICAO_IDEAL)
      return (pa->igual - pb->igual);
  if (pa->dist == pb->dist)
      return ((pa->dist >= 2 && pa->dist <= RANGE_INIMIGO) - (pb->dist >= 2 && pb->dist <= RANGE_INIMIGO));
	return pa->dist - pb->dist;
}

/**
\brief Funcao que decide o movimento de um inimigo
@param e Estado atual do jogo
@param i Posicao do inimigo a ser movido, no array dos inimigos
@param tipo Tipo do inimigo a ser movimentado
@returns Estado com o movimento do inimigo efectuado.

* Cada posicao a volta do inimigo é testada para ver se é valida.
* Se for, é acrescentada a um array de estrutura 'POS_DIST2', com as carateristicas
* de cada casa individual, para depois ser sorteada conforme o 'comparator2'.
*/
ESTADO mover_inimigo_ranged(ESTADO e, int i, int tipo){
  POS_DIST2 viz[9];
  int num_viz = 0;
  int dx, dy, valor_mat;
  int novo_x = e.inimigo[tipo][i].coord.x, novo_y = e.inimigo[tipo][i].coord.y;
  int posx = novo_x, posy = novo_y;

  for (dx = -1; dx <= 1; dx++){
    for (dy = -1; dy <= 1; dy++){
      valor_mat = matriz[posy + dy][posx + dx];
      if(posicao_valida(posx + dx, posy + dy) && !posicao_ocupada(e, posx + dx, posy + dy) && !tem_bau(e, posx + dx, posy + dy)){
        novo_y = posy + dy;
        novo_x = posx + dx;
        viz[num_viz].x = novo_x;
        viz[num_viz].y = novo_y;
        viz[num_viz].dist = valor_mat;
        viz[num_viz].igual = IGUAL(e.jog.coord.x, e.jog.coord.y, posx + dx, posy + dy);
        viz[num_viz].obstaculo = (procura_obscatulos(e, posx + dx, 0) || procura_obscatulos(e, 0, posy + dy));
        viz[num_viz].rnd = random();
        num_viz++;
      }
    }
  }
  qsort(viz, num_viz, sizeof(POS_DIST2), comparator2);
  e.inimigo[tipo][i].coord.x = viz[0].x;
  e.inimigo[tipo][i].coord.y = viz[0].y;
  return e;
}

/**
\brief Metodo de organicao do array das novas posicoes, possiveis, do inimigo
* Se tiverem a mesma distancia ao jogador, o que tiver menor valor no 'rnd'
* fica primeiro, senao, o que tiver menor distancia fica primeiro
*/
int comparator(const void * a, const void *b) {
	POS_DIST *pa = (POS_DIST *) a;
	POS_DIST *pb = (POS_DIST *) b;
	if(pa->dist == pb->dist)
		return ((pa->rnd - pb->rnd) % 11);
	return pa->dist - pb->dist;
}

/**
\brief Funcao que decide o movimento do inimigo normal
@param e Estado atual do jogo
@param i Posicao do inimigo a ser movido, no array dos inimigos
@param tipo Tipo do inimigo a ser movimentado
@returns Estado com o movimento do inimigo efectuado.

* Cada posicao a volta do inimigo é testada para ver se é valida.
* Se for, é acrescentada a um array de estrutura 'POS_DIST', com as carateristicas
* de cada casa individual, para depois ser sorteada conforme o 'comparator'.
*/
ESTADO mover_inimigo(ESTADO e, int i, int tipo) {
	POS_DIST viz[9];
	int num_viz = 0;
	int dx, dy, valor_mat;
	int novo_x = e.inimigo[tipo][i].coord.x, novo_y = e.inimigo[tipo][i].coord.y;
	int posx = novo_x, posy = novo_y;

	for (dx = -1; dx <= 1; dx++){
		for (dy = -1; dy <= 1; dy++){
			valor_mat = matriz[posy + dy][posx + dx];
			if(posicao_valida(posx + dx, posy + dy) && !posicao_ocupada(e, posx + dx, posy + dy) && !tem_bau(e, posx + dx, posy + dy)){
				novo_y = posy + dy;
				novo_x = posx + dx;
				viz[num_viz].x = novo_x;
				viz[num_viz].y = novo_y;
				viz[num_viz].dist = valor_mat;
				viz[num_viz].rnd = random();
				num_viz++;
			}
		}
	}
	qsort(viz, num_viz, sizeof(POS_DIST), comparator);
	e.inimigo[tipo][i].coord.x = viz[0].x;
	e.inimigo[tipo][i].coord.y = viz[0].y;
	return e;
}

/**
\brief Gera movimentos para todos os inimigos
@param e Estado atual do jogo
@returns Estado depois da acao efetuada.
* Se o inimigo puder atacar, ataca (r = 1), senao nao ataca (r = 0)
* CONDITION_TO_MOVE - apenas se certos inimigos morrerem, em certas quantidades
* é que faz com que o inimigo tipo 3 se mexa
*/
ESTADO movimentos_inimigos(ESTADO e){
	int i, r = 0;
	for (i = 0; i < e.num_inimigos1; i++){
		r = ataque_dos_inimigos(&e, i, 0);
		if(!r) e = mover_inimigo(e, i, 0);
	}

	for (i = 0; i < e.num_inimigos2; i++){
		r = ataque_dos_inimigos_ranged(&e, i, 1);
		if (!r) e = mover_inimigo_ranged(e, i, 1);
	}

	if (CONDITION_TO_MOVE){
		for (i = 0; i < e.num_inimigos3; i++){
			r = ataque_dos_inimigos(&e, i, 2);
			if(!r) e = mover_inimigo(e, i, 2);
		}
	}
	return e;
}
