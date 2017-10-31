#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estado.h"
#include "cgi.h"
#include "images.h"
#include "prototipos.h"

char *images_Easteregg[]={
	"easteregg1.jpg",
	"easteregg2.png",
	"easteregg3.png",
	"easteregg4.jpg",
	"easteregg5.jpg"
};
char *images[]={
	"Nivel1.png",
	"Nivel2.jpg",
	"Nivel3.png",
	"Nivel4.png",
	"Nivel5.jpg",
	"Chao1.png",
	"Chao2.jpg",
	"Chao3.jpg",
	"Chao4.jpg",
	"Chao5.png",
	"wall1.png",
	"wall2.jpg",
	"wall3.jpg",
	"wall4.png",
	"Obstaculo1.png",
	"Obstaculo2.png",
	"Obstaculo3.png",
	"Vida.png",
	"Jogador.png",
	"Saida1.png",
	"Inimigolvl1.png",
	"click_easteregg.png",
	"ataca.png",
	"start.png",
	"restart.png",
	"powerUp_ataca.png",
	"armor.png",
	"Vida.png",
	"genki_dama.png",
	"vegeta.png",
	"hitto.png"
};

/**
@file game.c
Ficheiro onde esta a main do jogo
*/

/**
* Variaveis Globais
*/
int parede, chao, bground, id_easter, obstac = OBSTACULO3;
extern int matriz[TAM][TAM];

/**
\brief Função que testa se uma posição é válida no mapa, se respeita os limites.
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se for valida, 0 se nao for
*/
int posicao_valida(int x, int y) {
	return x >= 1 && y >= 1 && x <= (TAM-2) && y <= (TAM-2);
}

/**
\brief Função que compara duas coordenadas, dizendo se são iguais ou não.
@param p Struct com a posicao a ser testada
@param x Coordenada x a ser testada em relacao a p
@param y Coordenada y a ser testada em relacao a p
@returns 1 se for igual, 0 se nao for
*/
int posicao_igual(POSITION p, int x, int y){
	return p.x == x && p.y == y;
}

/**
\brief Função que testa se uma posição tem baú
@param e Estado atual do jogo
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se tiver bau, 0 se nao tiver
*/
int tem_bau(ESTADO e, int x, int y){
	int i;
	for (i = 0; i < e.num_baus; i++)
		if (posicao_igual(e.bau[i].coord, x, y))
			return 1;
	return 0;
}

/**
\brief Função que testa se uma posição está ocupada por um obstáculo.
@param e Estado atual do jogo
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se tiver obstaculo, 0 se nao tiver
*/
int tem_obstaculo(ESTADO e, int x, int y){
	int i;
	for (i = 0; i < e.num_obstaculos; i++)
		if (posicao_igual(e.obstaculo[i].coord, x, y))
			return 1;
	return 0;
}

/**
\brief Função que testa se uma posição está ocupada por um inimigo.
@param e Estado atual do jogo
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se tiver inimigo, 0 se nao tiver
*/
int tem_inimigo(ESTADO e, int x, int y){
	int i;
	for (i = 0; i < e.num_inimigos1; i++)
		if (posicao_igual(e.inimigo[0][i].coord, x, y))
			return 1;

	for (i = 0; i < e.num_inimigos2; i++)
		if (posicao_igual(e.inimigo[1][i].coord, x, y))
			return 1;

	for (i = 0; i < e.num_inimigos3; i++)
		if (posicao_igual(e.inimigo[2][i].coord, x, y))
			return 1;


	return 0;
}

/**
\brief Função que testa se uma posição está ocupada por um jogador.
@param e Estado atual do jogo
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se tiver jogador, 0 se nao tiver
*/
int tem_jogador(ESTADO e, int x, int y){
	return posicao_igual(e.jog.coord, x, y);
}

/**
\brief Função que testa se uma posição está ocupada por uma saída.
@param e Estado atual do jogo
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se tiver saida, 0 se nao tiver
*/
int tem_saida(ESTADO e, int x, int y){
  return posicao_igual(e.saida, x, y);
}

/**
\brief Função que averigua se a posição está ocupada ou livre.
@param e Estado atual do jogo
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se estiver ocupada, 0 se nao estiver
*/
int posicao_ocupada(ESTADO e, int x, int y){
	return tem_jogador(e, x, y) || tem_obstaculo(e, x, y) || tem_inimigo(e, x ,y) || tem_saida(e, x, y);
}

/**
\brief Função que testa se um movimento é válido.
@param e Estado atual do jogo
@param x Coordenada x a ser testada
@param y Coordenada y a ser testada
@returns 1 se nao for valido, 0 se for
* Utilizando as funções tem_obstaculo, tem_inimigo e tem_jogador a função
* diz se o jogador se pode movimentar para a posição desejada.
*/
int mov_valido(ESTADO e, int x, int y){
	return tem_obstaculo(e, x, y) || tem_inimigo(e, x ,y) || tem_jogador(e, x, y);
}

/**
\brief Função que permite que o jogador se mova no início do jogo.
@param x Coordenada x a ser verificada
@param y Coordenada y a ser verificada
@returns 1 se pertencer a borda, 0 se nao pertencer
* É aqui definido que nada pode ser imprimido nas posições (2,10), (2,9) e (1,9)
* para que o jogador possa sempre iniciar o jogo e nunca esteja preso.
*/
int limite(int x, int y){
	return (((x == 2) && y == 10) || ((y == 9) && x == 2) || ((y == 9) && x == 1));
}

/**
\brief Coloca disponível o ataque especial nas casas á volta do jogador
@param e
@param dx Coordenada x da direcao do ataque
@param dy Coordenada y da direcao do ataque
* Imprime no ecra hiperligacoes para o ataque especial
*/
void ataca_beam_casa(ESTADO e, int dx, int dy){
  int x = e.jog.coord.x + dx;
  int y = e.jog.coord.y + dy;
  char link[MAX_BUFFER];

  if(!posicao_valida(x, y))
    return;

  sprintf(link, "http://localhost/cgi-bin/game?pwubeam-%d,%d", x, y);
  ABRIR_LINK(link);
  printf("<image x=%d y=%d width=%d height=%d xlink:href = %sMisc/seleciona.png />", x*SCALE, y*SCALE, SCALE, SCALE, IMAGE_PATH);
  FECHAR_LINK;
}

/**
\brief Função que torna possível escolher o sentido do ataque especial
@param e Estado do jogo
* Torna possível atacar uma linha na direção pretendida.
*/
void print_ataca_beam(ESTADO e){
  ataca_beam_casa(e, 1, 0);
  ataca_beam_casa(e, -1, 0);
  ataca_beam_casa(e, 0, 1);
  ataca_beam_casa(e, 0, -1);
}

/**
\brief Função que desenha no mapa um baú com certos conteúdos.
@param e Estado do jogo
*/
void print_bau(ESTADO e){
	int i;
	for (i = 0; i < e.num_baus; i++)
		PRINT_IMAGE(e.bau[i].coord.x, e.bau[i].coord.y, MISC, e.bau[i].content);
}

/**
\brief Função que desenha no mapa um espaço dedicado ao reiniciamento do jogo
*/
void print_restart(){
		ABRIR_LINK("http://localhost/cgi-bin/game?novo");
		PRINT_IMAGE(26, 6, MISC, RESTART);
		FECHAR_LINK;
}

/**
\brief Função que desenha no jogo um espaço dedicado á explicação das suas regras
*/
void print_regras(){
	printf("<a target=_blank xlink:href=http://localhost/cgi-bin/duvida>\n");
	printf("<image x=1225 y=10 width=%d height=%d xlink:href = %sMisc/ajuda.jpg />\n", 250, 250, IMAGE_PATH);
	FECHAR_LINK;
}

/**
\brief Função que imprime no ecra as informacoes relativas ao jogador
@param e Estado atual do jogo
* Imprime no ecra a percentagem de armadura, de vida e, se estiver com stamina que chegue,
* imprime uma hiperligacao com a possibilidade de usar o ataque especial
*/
void print_stats(ESTADO e){
	int i = 1;
  int x = VD_X;
  while (i <= (int)e.jog.n_vidas){
    PRINT_IMAGE(x, VD_Y, MISC, VIDA);
    x++;
    i++;
  }
	printf("<image x=1540 y=500 width=250 height=250 xlink:href = %sMisc/armor.png />\n", IMAGE_PATH);

	if ((int)e.jog.armadura >= 0)
			printf(" <text x=1800 y=600 fill=red font-size=40>\n %f%% \n</text>\n", e.jog.armadura);
	else
	 		printf(" <text x=1800 y=600 fill=red font-size=40>\n 0%% \n</text>\n");
	if (e.jog.stamina == 4){
		ABRIR_LINK("http://localhost/cgi-bin/game?beam");
		printf("<image x=900 y=560 width=200 height=200 xlink:href = %sMisc/genki_dama.png />\n", IMAGE_PATH);
		FECHAR_LINK;
	}
	if (e.jog.beam) print_ataca_beam(e);
}

/**
\brief Função que desenha o chão e bordas do mapa.
* Uilizando uma condição para saber se as coordenadas são de bordas ou chão.
* 0 e 11 equivalem paredes (borda)
@param e Estado atual do jogo
*/
void print_board(ESTADO e){
  int l,c;

  for (l = 0; l < TAM; l++){
    for (c = 0; c < TAM; c++){
      if (l==0 || l==TAM-1 || c==0 || c==TAM-1)
        PRINT_IMAGE(c, l, WALLS, parede);
      else  PRINT_IMAGE(c, l, FLOORS, chao);
    }
  }
	PRINT_IMAGE(e.saida.x, e.saida.y, SAIDAS, SAIDA);
}

/**
\brief Função que desenha o jogador.
@param e Estado atual do jogo
*/
void print_player(ESTADO e){
	PRINT_IMAGE(e.jog.coord.x, e.jog.coord.y, MISC, JOGADOR);
	print_stats(e);
  imprime_movimentos(e);
}
/**
\brief Função que desenha no mapa obstáculos.
@param e Estado atual do jogo
*/
void print_obstaculos(ESTADO e){
  int i;
  for (i=0; i<e.num_obstaculos; i++)
    PRINT_IMAGE (e.obstaculo[i].coord.x, e.obstaculo[i].coord.y, OBSTACULOS, obstac);
}

/**
\brief Função que desenha no mapa inimigos.
@param e Estado atual do jogo
*/
void print_inimigos(ESTADO e){
  int i;
  for (i = 0; i < e.num_inimigos1; i++)
		PRINT_IMAGE (e.inimigo[0][i].coord.x, e.inimigo[0][i].coord.y, INIMIGOSLVL1, INIMIGOLVL1_1);

  for (i = 0; i < e.num_inimigos2; i++)
  	PRINT_IMAGE (e.inimigo[1][i].coord.x, e.inimigo[1][i].coord.y, INIMIGOSLVL3, INIMIGOLVL1_2);

  for (i = 0; i < e.num_inimigos3; i++)
  	PRINT_IMAGE (e.inimigo[2][i].coord.x, e.inimigo[2][i].coord.y, INIMIGOSLVL5, INIMIGOLVL1_3);

}
/**
\brief Função que permite o jogador abrir baús.
@param Utiliza o estado e as coordenadas do jogador
@returns Retorna novos stats no jogador e atualizações no estado
* Utiliza um switch para que se possa saber o powerUp que vai ser dado ao jogador
*/
ESTADO abre_bau(ESTADO e, int x, int y){
	int i = 0;
	while (!posicao_igual(e.bau[i].coord, x, y))
		i++;
	switch (e.bau[i].content){
		case PWU_VIDA :
				if (e.jog.n_vidas < MAX_VIDAS) e.jog.n_vidas += 1;
				break;

		case PWU_ARMOR :
				if (e.jog.armadura < MAX_ARMOR) e.jog.armadura += 50.0;
				break;

		case PWU_ATAQUE :
				e.jog.ataque += 0.5;
				break;
	}

	e.num_baus -= 1;
	e.bau[i] = e.bau[e.num_baus];
	e.jog.coord.x = x;
	e.jog.coord.y = y;

	return e;
}


/**
\brief Função que gera um movimento se tal for possível.
@param e Estado atual do jogo
@param dx Somando á coordenada x do jogador, representa a nova posicao x
@param dy Somando á coordenada y do jogador, representa a nova posicao y
* As coordenadas geradas em imprime_movimentos são adicionadas ás coordenadas da posição
* atual do jogador, que vão ser testadas pelas funções posicao_valida e mov_valido para se saber se o movimento pode ser efetuado.
* Se a resposta for sim então vai ser gerada uma imagem do jogador na casa seguinte desaparecendo da anterior.
*/
void imprime_movimento(ESTADO e, int dx, int dy) {
	int x = e.jog.coord.x + dx;
	int y = e.jog.coord.y + dy;
	char link[MAX_BUFFER];

	if(!posicao_valida(x, y))
		return;
	if(mov_valido(e, x, y))
		return;
	if(tem_bau(e, x, y))
		return;

	sprintf(link, "http://localhost/cgi-bin/game?move-%d,%d", x, y);
	ABRIR_LINK(link);
  printf("<rect x=%d y=%d width=%d height=%d fill=white fill-opacity=0.0 />", x*SCALE, y*SCALE, SCALE, SCALE);
	FECHAR_LINK;
}

/**
\brief Função que gera um ataque do jogador se tal for possível, atraves de uma hiperlifacao
@param e Estado atual do jogo
@param dx Somando á coordenada x do jogador, representa a nova posicao x
@param dy Somando á coordenada y do jogador, representa a nova posicao y
* Se a posição pretendida para atacar possuir um inimigo então um
* ataque será feito
*/
void imprime_ataque_jog(ESTADO e, int dx, int dy) {
	int x = e.jog.coord.x + dx;
	int y = e.jog.coord.y + dy;
	char link[MAX_BUFFER];

	if(!tem_inimigo(e, x, y))
		return;

	sprintf(link, "http://localhost/cgi-bin/game?ataca-%d,%d", x, y);
	ABRIR_LINK(link);
  printf("<rect x=%d y=%d width=%d height=%d fill=white fill-opacity=0.0 />", x*SCALE, y*SCALE, SCALE, SCALE);
	FECHAR_LINK;
}

/**
\brief Função que permite abrir um baú, atraves de uma hiperligacao
@param e Estado atual do jogo
@param dx Somando á coordenada x do jogador, representa a nova posicao x
@param dy Somando á coordenada y do jogador, representa a nova posicao y
*/
void imprime_mov_pra_bau(ESTADO e, int dx, int dy){
	int x = e.jog.coord.x + dx;
	int y = e.jog.coord.y + dy;
	char link[MAX_BUFFER];

	if(!tem_bau(e, x, y))
		return;
	sprintf(link, "http://localhost/cgi-bin/game?bau-%d,%d", x, y);
	ABRIR_LINK(link);
  printf("<rect x=%d y=%d width=%d height=%d fill=white fill-opacity=0.0 />", x*SCALE, y*SCALE, SCALE, SCALE);
	FECHAR_LINK;
}

/**
\brief Função que gera os movimentos possíveis de um jogador.
@param e Estado do jogo
* Gera movimentos possíveis. sendo estes para a frente, para trás, cima, baixo e diagonais.
* São utilizados dois ciclos para tanto em x como em y serem gerados valores,
* sendo estes = {-1,0,+1}.
*/
void imprime_movimentos(ESTADO e) {
	int dx, dy;

	for (dx= -1; dx <= 1; dx++)
		for (dy = -1; dy <= 1; dy++){
			if (!e.jog.beam){
				imprime_movimento(e, dx, dy);
				imprime_mov_pra_bau(e, dx, dy);
				imprime_ataque_jog(e, dx, dy);
			}
		}
}

/**
\brief Função que gera uma saída no mapa.
@param e Estado do jogo
* Gera uma saida no mapa, fixando a posição na primeira linha pois
* pretende-se que a saída esteja no topo do mapa.
* É utilizada a função rand para que a saída seja aleatória na primeira linha.
*/
ESTADO inicializar_saida(ESTADO e){
  int y = 1;
  int x;
  do{
    x = random() % (TAM-2) + 1;
  } while (posicao_ocupada(e, x, y));

  e.saida.x = x;
  e.saida.y = y;

  return e;
}

/**
\brief Função que gera as posições dos obstáculos.
@param e Estado do jogo
* Gera posições aleatórias (usando o rand), utilizada a função posicao_ocupada e limite
* para que não sejam gerados quaisquer obtáculos em locais ocupados por outros.
* Depois de gerar guarda na estrutura ESTADO, no respetivo campo "obstaculo".
*/
ESTADO inicializar_obstaculo(ESTADO e){
  int x, y;
  do{
    x = random() % (TAM-2) + 1;
    y = random() % (TAM-2) + 1;
  } while (posicao_ocupada(e, x, y) || limite(x, y));
  e.obstaculo[e.num_obstaculos].coord.x = x;
  e.obstaculo[e.num_obstaculos].coord.y = y;
	e.obstaculo[e.num_obstaculos].vida = 2;

  e.num_obstaculos++;
  return e;
}
/**
\brief Esta função chama a função inicializar_obstatulo.
@param e Estado atual do jogo
@param num Numero de obstaculos a serem criados
* Função que cria uma quantidade de obstaculos.
* Para que tal aconteça é criado um ciclo que acaba quando i igualar num.
*/
ESTADO inicializar_obstaculos(ESTADO e, int num){
  int i;
  for (i = 0; i < num; i++)
    e = inicializar_obstaculo(e);

  return e;
}

/**
\brief Função que gera as posições dos inimigos de tipo 1
@param e Estado do jogo
@param tipo Tipo de inimigo a ser gerado
* Enquanto as posições estiverem ocupadas são gerados números aleatrórios para
* gerar coordenadadas unicas para o inimigo, assim como as suas condicoes
*/
ESTADO inicializar_inimigo1(ESTADO e, int tipo){
	int x, y;
	do {
		x = random() % (TAM-2) + 1;
  	y = random() % (TAM-2) + 1;
	} while (posicao_ocupada(e, x, y) || limite(x, y));
	e.inimigo[tipo][e.num_inimigos1].coord.x = x;
	e.inimigo[tipo][e.num_inimigos1].coord.y = y;
	e.inimigo[tipo][e.num_inimigos1].vida = 2.0;
	e.inimigo[tipo][e.num_inimigos1].ataque = 0.4;

	e.num_inimigos1++;
	return e;
}

/**
\brief Função que gera as posições dos inimigos de tipo 2
@param e Estado do jogo
@param tipo Tipo de inimigo a ser gerado
* Enquanto as posições estiverem ocupadas são gerados números aleatrórios para
* gerar coordenadadas unicas para o inimigo, assim como as suas condicoes
*/
ESTADO inicializar_inimigo2(ESTADO e, int tipo){
	int x, y;
	do{
		x = random() % (TAM-2) + 1;
		y = random() % (TAM-2) + 1;
	} while (posicao_ocupada(e, x, y) || limite(x, y));
	e.inimigo[tipo][e.num_inimigos2].coord.x = x;
	e.inimigo[tipo][e.num_inimigos2].coord.y = y;
	e.inimigo[tipo][e.num_inimigos2].vida = 1;
	e.inimigo[tipo][e.num_inimigos2].ataque = 1.5;

	e.num_inimigos2++;
	return e;
}

/**
\brief Função que gera as posições dos inimigos de tipo 3
@param e Estado do jogo
@param tipo Tipo de inimigo a ser gerado
* Enquanto as posições estiverem ocupadas são gerados números aleatrórios para
* gerar coordenadadas unicas para o inimigo, assim como as suas condicoes
*/
ESTADO inicializar_inimigo3(ESTADO e, int tipo){
	int x, y;
	do{
		x = random() % (TAM-2) + 1;
		y = random() % (TAM-2) + 1;
	} while (posicao_ocupada(e, x, y) || limite(x, y));
	e.inimigo[tipo][e.num_inimigos3].coord.x = x;
	e.inimigo[tipo][e.num_inimigos3].coord.y = y;
	e.inimigo[tipo][e.num_inimigos3].vida = 4.0;
	e.inimigo[tipo][e.num_inimigos3].ataque = 0.8;

	e.num_inimigos3++;
	return e;
}
/**
\brief Esta função chama a função inicializar_inimigos.
@param e Estado do jogo
@param normais Quantidade de inimigos normais a ser criados
@param medios Quantidade de inimigos medios a ser criados
@param fortes Quantidade de inimigos fortes a ser criados
* Função que define quantos inimigos sao criados, de cada tipo.
* Para que tal aconteça é criado um ciclo que acaba quando i igualar esse numero.
*/
ESTADO inicializar_inimigos(ESTADO e, int normais, int medios, int fortes){
  int i;
  for (i = 0; i < normais ; i++)
    e = inicializar_inimigo1(e, 0);
  for (i = 0; i < medios; i++)
  	e = inicializar_inimigo2(e, 1);
  for (i = 0; i < fortes; i++)
  	e = inicializar_inimigo3(e, 2);

  return e;
}

/**
\brief Função que gera coordenadas para o bónus especial no jogo.
*/
ESTADO inicializar_easteregg(ESTADO e){
  int x,y;
	do {
	    x = random() % (TAM-2) + 1;
	    y = random() % (TAM-2) + 1;
	} while (posicao_ocupada(e, x, y));
	  e.easteregg.x = x;
	  e.easteregg.y = y;
  return e;
}

/**
\brief Função que gera baús, aleatoriamente
@param e Estado do jogo (onde se irá escrever)
@returns Estado com baus
*/
ESTADO inicializar_bau(ESTADO e){
	int r, i, t;
	int x, y;
	r = random()% MAX_BAUS + 1;
	e.num_baus = r;

	for (i = 0; i < r; i++){
		do {
			x = random() % (TAM-2) + 1;
	    y = random() % (TAM-2) + 1;
		} while (posicao_ocupada(e, x, y) || limite(x, y) || tem_bau(e, x, y));
		e.bau[i].coord.x = x;
		e.bau[i].coord.y = y;

		t = random() % (27-25)+25;
		e.bau[i].content = t;
	}
	return e;
}
/**
\brief É a função responsável pela criação de níveis.
* Esta contém a posição inicial do jogador, sendo esta constate, as vidas
* e o nivel para identificar o nível.
* É aconpanhada de funções como inicializar_inimigos, inicializar_obstaculos, inicializar_saida
* e inicializar_easteregg.
*/
ESTADO inicializar(){
	ESTADO e = {0}; /*tudo comeca a zero*/

	e.jog.coord.x = 1;
  e.jog.coord.y = 10; /*Possivel geraçao random*/
	e.jog.n_vidas = 3;
	e.jog.armadura = 25.0;
	e.jog.ataque = 1;
	e.nivel = 1;

  e = inicializar_inimigos(e, MAX_INIMIGOS1, MAX_INIMIGOS2, MAX_INIMIGOS3);
  e = inicializar_obstaculos(e, MAX_OBSTACULOS);
  e = inicializar_saida(e);
  e = inicializar_easteregg(e);
	e = inicializar_bau(e);
	matriz_mapa(&e);
  return e;
}

/**
\brief Função que verifica se o jogador chegou á saída utilizando a função posicao_igual.
* Se a condição se verificar então é adicionada 1 ao nível onde o jogador se encontra e utilizando
* a funçao inicializar é gerado o próximo nível.
* Primeiro guarda o nivel e as vidas atuais, de seguida reinicia-se o estado e
* depois são restauradas os valores ao estado.
*/
ESTADO passa_de_nivel(ESTADO e){
  float vidas, armadura, ataque;
	int nivel, stamina, score, ini_derrotados;

    if (posicao_igual(e.saida, e.jog.coord.x, e.jog.coord.y)){
			if(e.nivel % 5 == 0) score = e.jog.score + 700;
			else score = e.jog.score + 200; //Passou de nivel = 200 pontos
      vidas = e.jog.n_vidas;
      nivel = 1 + e.nivel;
			ataque = e.jog.ataque;
			armadura = e.jog.armadura;
			stamina = e.jog.stamina;
			ini_derrotados = e.jog.ini_derrotados;

      e = inicializar();   /*Aqui fica tudo o que será mantido de um nivel pro outro*/

      e.nivel = nivel;
			e.jog.stamina = stamina;
      e.jog.n_vidas = vidas;
			e.jog.armadura = armadura;
			e.jog.ataque = ataque;
			e.jog.score = score;
			e.jog.ini_derrotados = ini_derrotados;

      return e;
    }
    return e;
}

/**
\brief Função responsável pela troca de imagen na passagem de nível.
* Foram definidos 5 casos para 5 níveis diferentes.
* @code e.nivel % 5@endcode Serve para averiguar em que nível estamos.
* Isto, porque como temos apenas combinações de imagens para 5 níveis diferentes,
* temos de conseguir voltar ás iniciais com base no nível presente.
* Cada caso corresponde a um nivel e ao seu correspondente conjunto de imagens.
*/
void define_imagens(ESTADO e){
	switch (e.nivel % 5) {
		case 0 :
				parede = PAREDE4;
				chao = CHAO5;
				bground = FUNDO5;
				obstac = OBSTACULO1;
				id_easter = 4;
				break;
		case 1 :
				parede = PAREDE2;
				chao = CHAO1;
				bground = FUNDO1;
				id_easter = 0;
				break;
		case 2 :
				parede = PAREDE2;
				chao = CHAO2;
				bground = FUNDO2;
				id_easter = 1;
				break;
		case 3 :
				parede = PAREDE2;
				chao = CHAO3;
				bground = FUNDO3;
				obstac = OBSTACULO2;
				id_easter = 2;
				break;
		case 4 :
				parede = PAREDE3;
				chao = CHAO4;
				bground = FUNDO4;
				obstac = OBSTACULO1;
				id_easter = 3;
				break;
	}
}

/**
\brief Gestao e aplicacao das diferentes acoes do jogador
@param args Argumento da 'QUERY_STRING' que contem a acao
@param e Estado atual do jogo
@return Estado depois de uma acao realizada pelo jogador.
*/
ESTADO aplica_acao(char *args, ESTADO e){
	char acao[10];
	int x;
	int y;
	sscanf(args, "%[^-]-%d,%d", acao, &x, &y);
	if (!strcmp(acao,"novo")){
	e = inicializar();
	}
	if (!strcmp(acao,"move")){
		if(x == e.jog.coord.x && y == e.jog.coord.y) return e; //evita a jogada de "permanecer no sitio"
		e.jog.coord.x = x;
		e.jog.coord.y = y;
		if (e.jog.stamina < 4) e.jog.stamina += 1;
		matriz_mapa(&e);
		e = movimentos_inimigos(e);
	}
	if (!strcmp(acao,"ataca")){
		ataca_o_inimigo(&e, x, y, e.jog.ataque);
		e = movimentos_inimigos(e);
	}
	if (!strcmp(acao,"beam")){
		e.jog.beam = !e.jog.beam;
	}
	if (!strcmp(acao,"pwubeam")){
		ataca_inimigo_beam(&e, x, y);
		e.jog.beam = 0;
		e.jog.stamina -= 4;
		e = movimentos_inimigos(e);
		e = movimentos_inimigos(e);
	}
	if (!strcmp(acao, "bau")){
		if(x == e.jog.coord.x && y == e.jog.coord.y) return e; //evita a jogada de "permanecer no sitio"
		e = abre_bau(e, x, y);
		e = movimentos_inimigos(e);
	}
	return e;
}

/**
\brief Função que verifica se o jogador morreu
Se o jogador morrer, passa para a página final
@param e Estado atual do jogo
*/
void morreu_jogador(ESTADO e){
	if (e.jog.n_vidas <= 0)
		printf("<meta http-equiv=refresh content=0;URL=http://localhost/cgi-bin/gameover />\n");
}

/**
\brief Função que altera o estado do jogo
@param me Apontador para o estado atual do jogo
@param args String com a acao na QUERY_STRING
*/
void altera_estado(ESTADO *me, char *args){
	ESTADO e = *me;
	e = aplica_acao(args, e);
	e = passa_de_nivel(e);
	e = enc_easteregg(e);
	*me = e;
}

/**
\brief Função responsável pelo tratamento do score do jogador, colocando-o num ficheiro
@param myscore Score atual do jogador
*/
void tratamento_score(int myscore){
	char *nome = "myscore";
	char filename[1024];
	sprintf(filename, "/var/www/html/user/%s", nome);

	FILE *score = fopen(filename, "r");

	if (score == NULL){
		perror("nao consegui abrir o ficheiro SCORE INICIO\n");
		exit(1);
	} /*ver se abriu*/

	escreve_pontos(score, filename, myscore);
}

/**
\brief Função que decide o "ponto" onde começa o jogo.
@param args String que contém o estado.
* Caso "args" esteja vazio, o jogo começa do início (fazendo um estado novo) se nao houver ficheiro de estado,
* ou se houver estado, retoma a partir deste
* Senão lê o existente e converte para um estado.
*/
void ler_estado(ESTADO *me, char *args){
	ESTADO e = *me;
	char *nome = "username";
	char filename[1024];
	sprintf(filename, "/var/www/html/user/%s", nome);

	FILE *state = fopen(filename, "r");

	if (state == NULL){
		perror("nao consegui abrir o ficheiro INICIO \n");
		exit(1);
	} /*ver se abriu*/

	char estado[10240];
	fscanf(state, "%s", estado);

	if (args == NULL || strlen(args) == 0){
		 if (strlen(estado) == '\0'){
			 e = inicializar();
		 	fclose(state);
		 	escreve_ficheiro(state, e, filename);
	   	}
		 else
		 	e = ler_ficheiro(state, filename);
	}
	else{
	 if(args != NULL && strlen(args) != 0){
		e = ler_ficheiro(state, filename);
		altera_estado(&e, args);
		escreve_ficheiro(state, e, filename);
	 }
	 e = ler_ficheiro(state, filename);
	}

	tratamento_score(e.jog.score);
	*me = e;
}

/**
\brief Função main onde são geradas as imagens e é inicializado o jogo.
* Esta função cria um 'estado', onde armazena todas as posições aleatór999ias
* (devido ao @code srandom(time(NULL))@endcode) de obstáculos, inimigos, saida,
* 'easteregg', etc.
* Depois gera o HTML e assim como o SVG..
* Por fim, ainda dentro do SVG, imprime no ecrã os obstáculos, imagens, inimigos, etc.

@code e = passa_de_nivel(e)@encode Avalia se o jogador chegou á saída. Se sim, o mapa recomeça.
@code e = enc_easteregg(e)@endcode Avalia se o jogador eFncontrou o 'easteregg'.
*/
int main(){
	ESTADO e;
	srandom(time(NULL));
	char *args = getenv("QUERY_STRING");

	ler_estado(&e, args);

	define_imagens(e);
	START_HTML;

	if (e.jog.n_vidas <= 1.5 && e.jog.armadura <= 0.0)
		printf("<audio src=http://localhost/images2.0/low_hp.mp3 autoplay loop>\
	Your browser does not support the audio element.\
	</audio>");

	HTML_OPEN_HEAD(TITULO);
	morreu_jogador(e);
	HTML_CLOSE_HEAD;
	HTML_BG(bground);

	START_SVG(1900,880);
	TABLE_RECTS;
	TABLE_TEXT(e);
	print_restart();

	print_regras();
	print_board(e);
	print_inimigos(e);
	print_obstaculos(e);
	print_bau(e);
	print_player(e);
	print_easteregg(e, id_easter);

	COPYRIGHTS;
	STOP_SVG;
	return 0;
}
