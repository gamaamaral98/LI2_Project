#include <stdio.h>
#include "prototipos.h"
#include "estado.h"
#include "cgi.h"

#define RAIO_BEAM	5

/**
@file ataques.c
Ficheiro que contem todas as funcoes relacionadas com ataques.
*/

/**
\brief Funcao que executa o ataque dos inimigos ao jogador
@param e Apontador para o estado atual do jogo
@param tipo Tipo do jogador
@param i Posicao do inimigo no array de inimigos (usado para saber o dano a ser feito)
* Altera o estado, mais concretamente a vida e a armadura do jogador
*/
void ataca(ESTADO *e, int tipo, int i){
			if(e->jog.armadura > 0) e->jog.armadura -= e->inimigo[tipo][i].ataque * 31; //temos de "converter para percentagens" á nossa maneira
			else e->jog.n_vidas -= e->inimigo[tipo][i].ataque;
}
/**
\brief Função que verifica se existe obstáculo entre o jogador e o inimigo a ser atacado.
* Se existir obstáculo, não ataca.
@param e Estado atual do jogo.
@param coordx coordenada de uma casa no eixo x.
@param coordy coordenada de uma casa no eixo y.
@returns 1 se tiver obstáculo, 0 se não tiver.
*/
int procura_obscatulos(ESTADO e, int coordx, int coordy){
  int dd;
  if (!coordy){
    if (coordx > e.jog.coord.x){
      for (dd = 1; e.jog.coord.x + dd <= coordx; dd++)
        if (tem_obstaculo(e, e.jog.coord.x + dd, e.jog.coord.y))
            return 1;
    }
    else {
      for (dd = 1; coordx + dd <= e.jog.coord.x; dd++)
        if (tem_obstaculo(e, coordx + dd, e.jog.coord.y))
            return 1;
    }
  }
  else {
    if (coordy > e.jog.coord.y){
      for (dd = 1; e.jog.coord.y + dd <= coordy; dd++)
        if (tem_obstaculo(e, e.jog.coord.x, e.jog.coord.y + dd))
          return 1;
    } else {
      for (dd = 1; coordy + dd <= e.jog.coord.y; dd++)
        if (tem_obstaculo(e, e.jog.coord.x, coordy + dd))
          return 1;
    }
  }
  return 0;
}

/**
\brief Função que permite "friendly fire" entre inimigos.
* A função procura inimigos que possam ser afetados pelos ataques de outros inimigos
* se encontrar, esses inimigos são afetados.
@param e Apontador para o estado atual do jogo.
@param coordx coordenadas de uma casa no eixo x.
@param coordy coordenadas de uma casa no eixo y.
@returns Altera o estado.
*/
void ataca_proprio_inimigo(ESTADO *e, int coordx, int coordy){
	int dd;
  if (!coordy){
    if (coordx > e->jog.coord.x){
      for (dd = 1; e->jog.coord.x + dd <= coordx; dd++)
            ataca_o_inimigo(e, e->jog.coord.x + dd, e->jog.coord.y, e->inimigo[1][e->num_inimigos2-1].ataque);
    }
    else {
      for (dd = 1; coordx + dd <= e->jog.coord.x; dd++)
				ataca_o_inimigo(e, coordx + dd, e->jog.coord.y, e->inimigo[1][e->num_inimigos2-1].ataque);
    }
  }
  else {
    if (coordy > e->jog.coord.y){
      for (dd = 1; e->jog.coord.y + dd <= coordy; dd++)
				ataca_o_inimigo(e, e->jog.coord.x, e->jog.coord.y + dd, e->inimigo[1][e->num_inimigos2-1].ataque);
    }
		else {
      for (dd = 1; coordy + dd <= e->jog.coord.y; dd++)
				ataca_o_inimigo(e, e->jog.coord.x, coordy + dd, e->inimigo[1][e->num_inimigos2-1].ataque);
    }
  }
}

/**
\brief Funcao que, se o inimigo ataca se puder.
@param e Apontador para o estado atual do jogo.
@param i Inimigo na posicao 'i' do array de inimigos.
@param tipo Tipo do inimigo.
@returns 1 se atacar, 0 se nao atacar
* Se o inimigo nao estiver no raio favoravel ao ataque, nao ataca.
* Tendo uma das coordenadas iguais ao jogador, ataca (se possivel, sem obstaculos)
*/
int ataque_dos_inimigos_ranged(ESTADO *e, int i, int tipo){
  int x = e->inimigo[tipo][i].coord.x;
  int y = e->inimigo[tipo][i].coord.y;
  if (matriz[y][x] > RANGE_INIMIGO) return 0; // se nao estiver na distancia correta, nao ataca

  if (x == e->jog.coord.x){
    if (!procura_obscatulos(*e, 0, y)){
      ataca(e, tipo, i);
			ataca_proprio_inimigo(e, 0, y);
      return 1;
    }
		else return 0;
  }

  if (y == e->jog.coord.y){
    if (!procura_obscatulos(*e, x, 0)){
      ataca(e, tipo, i);
			ataca_proprio_inimigo(e, x, 0);
      return 1;
    }
		else return 0;
  }

  return 0;
}

/**
\brief Função que permite os inimigos atacar
@param e Estado que vai ser "estudado"
@param i Representa o inimigo que está a ser avaliado
@param tipo Representa o tipo de inimigo em causa
@returns 1 se atacar, 0 se nao atacar
* Função que executa o ataque dos inimigos, se estiver no raio de ataque ao jogador
* , retirando armadura se existente, ou vida
*/
int ataque_dos_inimigos(ESTADO *e, int i, int tipo){
	if(posicao_igual(e->inimigo[tipo][i].coord, e->jog.coord.x + 1, e->jog.coord.y)){
		ataca(e, tipo, i);
    return 1;
	}
	if(posicao_igual(e->inimigo[tipo][i].coord, e->jog.coord.x - 1, e->jog.coord.y)){
		ataca(e, tipo, i);
    return 1;
	}
	if(posicao_igual(e->inimigo[tipo][i].coord, e->jog.coord.x, e->jog.coord.y + 1)){
		ataca(e, tipo, i);
    return 1;
	}
	if(posicao_igual(e->inimigo[tipo][i].coord, e->jog.coord.x, e->jog.coord.y + 2)){
		ataca(e, tipo, i);
    return 1;
	}
  return 0;
}

/**
\brief Função que procura se existe obstaculo nas coordenadas passadas
@param e Representa o estado do jogo
@param x Coordenada x a ser avaliada
@param y Coordenada y a ser avaliada
@returns
Retorna o índice do obstáculo no array correspondente (se existir), senao retorna 999 (nao existe obstaculo)
*/
int procura_obstaculo(ESTADO e, int x, int y){
	int i;
	for (i = 0; i < e.num_obstaculos; i++){
		if (posicao_igual(e.obstaculo[i].coord, x, y))
			return i;
	}
	return 999;
}

/**
\brief Função que verifica o inimigo a ser atacado pelo jogador
@param dano Inteiro que representa o dano que os inimigos vão levar
@param tipo Inteiro que representa o tipo do inimigo
@returns Altera o estado
*/
void verifica_inimigo(ESTADO *e, int x, int y, int i, int dano, int tipo){
  if (posicao_igual(e->inimigo[tipo][i].coord, x, y)){
    e->inimigo[tipo][i].vida -= dano;
    if (e->inimigo[tipo][i].vida <= 0){
      if ( tipo == 0 ){e->num_inimigos1 -= 1; e->inimigo[tipo][i] = e->inimigo[tipo][e->num_inimigos1]; e->jog.score += 50;} // matou inimigo
      if ( tipo == 1 ){e->num_inimigos2 -= 1; e->inimigo[tipo][i] = e->inimigo[tipo][e->num_inimigos2]; e->jog.score += 100;}
      if ( tipo == 2 ){e->num_inimigos3 -= 1; e->inimigo[tipo][i] = e->inimigo[tipo][e->num_inimigos3]; e->jog.score += 150;}

      e->jog.ini_derrotados += 1;
    }
  }
}
/**
\brief Função que ataca os inimigos chamando verifica_inimigo
@param e Apontador para o estado atual
@param x Coordenada x a ser verificada (se tem inimigo)
@param y Coordenada y a ser verificada (se tem inimigo)
@param dano Inteiro que representa o dano do jogador
@returns Nada
* Chamando a verifica_inimigo, rastreia cada inimigo, de cada tipo, se vai ser afetado pelo ataque ou nao
*/
void ataca_o_inimigo(ESTADO *e, int x, int y, int dano){
  int i;
  for (i = 0; i < e->num_inimigos1; i++){
    verifica_inimigo(e, x, y, i, dano, 0);
  }

  for (i = 0; i < e->num_inimigos2; i++){
    verifica_inimigo(e, x, y, i, dano, 1);
  }

  for (i = 0; i < e->num_inimigos3; i++){
    verifica_inimigo(e, x, y, i, dano, 2);
  }
}

/**
\brief Ataca os inimigos com o ataque especial
@param e Apontador para o estado atual do jogo
@param dx Coordenada x da direcao do ataque
@param dy Coordenada y da direcao do ataque
@returns
* Altera o estado, caso inimigos e/ou obstáculos estejam no raio de ataque do "laser"
* Quando inimigos ou obstáculos estão no seu raio o array destes é atualizado sendo diminuido o número de obstáculos e
* inimigos, se este os matar
*/
void ataca_inimigo_beam(ESTADO *e, int dx, int dy){
	int i, n, obs;
	if (dx == e->jog.coord.x + 1){
		for (i = 1; i <= RAIO_BEAM; i++){
			n = e->jog.coord.x + i;
			if (tem_obstaculo(*e, n, dy)){
				obs = procura_obstaculo(*e, n, dy);
				e->num_obstaculos -= 1;
				e->obstaculo[obs] = e->obstaculo[e->num_obstaculos];
				break;
			}
			ataca_o_inimigo(e, n, dy, 2);
		}
	}
	if (dx == e->jog.coord.x - 1){
		for (i = 1; i <= RAIO_BEAM; i++){
			n = e->jog.coord.x - i;
			if (tem_obstaculo(*e, n, dy)){
				obs = procura_obstaculo(*e, n, dy);
				e->num_obstaculos -= 1;
				e->obstaculo[obs] = e->obstaculo[e->num_obstaculos];
				break;
			}
			ataca_o_inimigo(e, n, dy, 2);
		}
	}
	if (dy == e->jog.coord.y + 1){
		for (i = 1; i <= RAIO_BEAM; i++){
			n = e->jog.coord.y + i;
			if (tem_obstaculo(*e, dx, n)){
				obs = procura_obstaculo(*e, dx, n);
				e->num_obstaculos -= 1;
				e->obstaculo[obs] = e->obstaculo[e->num_obstaculos];
				break;
			}
			ataca_o_inimigo(e, dx, n, 2);
		}
	}
	if (dy == e->jog.coord.y - 1){
		for (i = 1; i <= RAIO_BEAM; i++){
			n = e->jog.coord.y - i;
			if (tem_obstaculo(*e, dx, n)){
				obs = procura_obstaculo(*e, dx, n);
				e->num_obstaculos -= 1;
				e->obstaculo[obs] = e->obstaculo[e->num_obstaculos];
				break;
			}
			ataca_o_inimigo(e, dx, n, 2);
		}
	}
}
