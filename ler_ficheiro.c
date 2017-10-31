#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "estado.h"
#define str(s) #s
#define ler_campo(fich, var, campo) if (fscanf(fich, str(campo)": %d", &var.campo) != 1){\
	fprintf(stderr, "nao consegui ler o campo" str(campo) "\n");\
	exit(1);\
}

/**
@file ler_ficheiro.c
Ficheiro responsável pela leitura do Estado do jogo.
*/

/**
\brief Função responsável pela leitura de todos os parâmetros do estado a partir de "jog.".
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
* Ou seja, tudo o que seja relacionado com o jogador.
*/
ESTADO set_jog(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	char argPos[10];
	sscanf(linha, "jog.%[^:]", argPos);
	if (!strcmp(argPos,"coord.x"))
		sscanf(valor, "%d", &e.jog.coord.x);
	if (!strcmp(argPos,"coord.y"))
		sscanf(valor, "%d", &e.jog.coord.y);
	if (!strcmp(argPos,"n_vidas"))
		sscanf(valor, "%f", &e.jog.n_vidas);
	if (!strcmp(argPos,"armadura"))
		sscanf(valor, "%f", &e.jog.armadura);
	if (!strcmp(argPos,"ataque"))
		sscanf(valor, "%f", &e.jog.ataque);
	if (!strcmp(argPos,"stamina"))
		sscanf(valor, "%d", &e.jog.stamina);
	if (!strcmp(argPos,"score"))
		sscanf(valor, "%d", &e.jog.score);
	if (!strcmp(argPos,"beam"))
		sscanf(valor, "%d", &e.jog.beam);
	if (!strcmp(argPos,"ini_derrotados"))
		sscanf(valor, "%d", &e.jog.ini_derrotados);
	return e;
}

/**
\brief Função responsável pela leitura de todos os parâmetros do estado a partir de "saida.".
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_saida(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	char argPos[10];
	sscanf(linha, "saida.%[^:]", argPos);
	if (!strcmp(argPos,"x"))
		sscanf(valor, "%d", &e.saida.x);
	if (!strcmp(argPos,"y"))
		sscanf(valor, "%d", &e.saida.y);

	return e;
}

/**
\brief Função responsável pela leitura de todos os parâmetros do estado a partir de "easteregg.".
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_egg(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	char argPos[10];
	sscanf(linha, "easteregg.%[^:]", argPos);
	if (!strcmp(argPos,"x"))
		sscanf(valor, "%d", &e.easteregg.x);
	if (!strcmp(argPos,"y"))
		sscanf(valor, "%d", &e.easteregg.y);

	return e;
}


/**
\brief Função responsável pela leitura do número de baús do jogo.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_num_bau(ESTADO e, char*linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(valor, "%d", &e.num_baus);
	return e;
}

/**
\brief Função responsável pela leitura do número de inimigos do tipo 1 do jogo.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_num_inimigos1(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(valor, "%d", &e.num_inimigos1);
	return e;
}

/**
\brief Função responsável pela leitura do número de inimigos do tipo 2 do jogo.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_num_inimigos2(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(valor, "%d", &e.num_inimigos2);
	return e;
}

/**
\brief Função responsável pela leitura do número de inimigos do tipo 3 do jogo.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_num_inimigos3(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(valor, "%d", &e.num_inimigos3);
	return e;
}

/**
\brief Função responsável pela leitura do número de obstáculos presentes no jogo.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_num_obstaculos(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(valor, "%d", &e.num_obstaculos);
	return e;
}

/**
\brief Função responsável pela leitura do nível onde o jogador se encontra.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_nivel(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(valor, "%d", &e.nivel);
	return e;
}

/**
\brief Função responsável pela leitura do encontro do easter_egg.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_enc_easter(ESTADO e, char *linha){
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(valor, "%d", &e.enc_easter);
	return e;
}

/**
\brief Função responsável pela leitura de todos os parâmetros do estado relacionados com o inimigo.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
* O seu tipo, posição, etc.
* A leitura é efetuada a partir de inimigo[tipo][i].
*/
ESTADO set_inimigo(ESTADO e, char *linha){
	int i, tipo;
	char arg[10];
	char index[10];
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(linha, "%*[^.].%[^:]", arg);
	sscanf(linha, "%*[^0123456789]%d]%[^.]", &tipo, index);
	sscanf(index, "[%d]", &i);
	if (!strcmp(arg,"coord.x"))
			sscanf(valor, "%d", &e.inimigo[tipo][i].coord.x);
	if (!strcmp(arg,"coord.y"))
			sscanf(valor, "%d", &e.inimigo[tipo][i].coord.y);
	if (!strcmp(arg,"vida"))
			sscanf(valor, "%f", &e.inimigo[tipo][i].vida);
	if (!strcmp(arg,"ataque"))
			sscanf(valor, "%f", &e.inimigo[tipo][i].ataque);
	return e;
}

/**
\brief Função responsável pela leitura de todos os parâmetros do etado relacionados com os obstáculos.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_obstaculo(ESTADO e, char *linha){
	int i;
	char arg[10];
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(linha, "%*[^.].%[^:]", arg);
	sscanf(linha, "%*[^0123456789]%d", &i);
	if (!strcmp(arg,"coord.x"))
			sscanf(valor, "%d", &e.obstaculo[i].coord.x);
	if (!strcmp(arg,"coord.y"))
			sscanf(valor, "%d", &e.obstaculo[i].coord.y);
	if (!strcmp(arg,"vida"))
			sscanf(valor, "%d", &e.obstaculo[i].vida);
	return e;
}

/**
\brief Função responsável pela leitura de todos os parâmetros do estado relacionados com os baús.
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO set_bau(ESTADO e, char *linha){
	int i;
	char arg[10];
	char valor[10240];
	sscanf(linha, "%*[^:]: %[^\n]", valor);
	sscanf(linha, "%*[^.].%[^:]", arg);
	sscanf(linha, "%*[^0123456789]%d", &i);
	if (!strcmp(arg,"coord.x"))
			sscanf(valor, "%d", &e.bau[i].coord.x);
	if (!strcmp(arg,"coord.y"))
			sscanf(valor, "%d", &e.bau[i].coord.y);
	if (!strcmp(arg,"content"))
			sscanf(valor, "%d", &e.bau[i].content);
	return e;
}

/**
\brief Funcao que chama uma funcao relacionada com cada linha
@param e Estado do jogo
@param linha Linha que contem a informacao a ser a lida
*/
ESTADO ler_campo_texto(ESTADO e, char *linha){
	struct{
		char *nome;
		ESTADO (*funcao)(ESTADO e, char *linha);
	} campos[]={
		{"num_baus", set_num_bau},
		{"bau", set_bau},
		{"jog", set_jog},
		{"saida", set_saida},
		{"easteregg", set_egg},
		{"num_inimigos1", set_num_inimigos1},
		{"num_inimigos2", set_num_inimigos2},
		{"num_inimigos3", set_num_inimigos3},
		{"num_obstaculos", set_num_obstaculos},
		{"nivel", set_nivel},
		{"enc_easter", set_enc_easter},
		{"inimigo", set_inimigo},
		{"obstaculo", set_obstaculo},
		{NULL,NULL}
	};
	char campo[100];
	sscanf(linha, "%[^:]:", campo);

	int i = 0;

	while(campos[i].nome != NULL && strstr(campo, campos[i].nome) == NULL) i++;

	if (campos[i].nome == NULL){
		fprintf(stderr, "campo %s nao existe\n", campo);
		exit(1);
	}
	return campos[i].funcao(e, linha);
}

/**
\brief Funcao que le um ficheiro e copia a informacao para o estado(do jogo)
@param state Ficheiro
@param filename Nome do ficheiro que contem o estado
*/
ESTADO ler_ficheiro(FILE *state, char *filename){
	ESTADO e = {0};
	state = fopen(filename, "r");
	if (state == NULL){
		perror("nao consegui abrir o ficheiro ");
		exit(1);
	}

	char linha[10240];
	while(fgets(linha, 10240, state) != NULL){
		e = ler_campo_texto(e, linha);
	}

	fclose(state);
	return e;
}
