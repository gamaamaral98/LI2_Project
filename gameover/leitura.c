#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgi.h"

/**
@file leitura.c
* Ficheiro para ler os top scores
*/

/**
\brief Funcao que le um valor de uma linha e coloca num array
@param valor Valor a ser colocado no array, originario da linha
@param linha Linha que contem a informacao
@param top_scores Array onde sera colocado os scores lidos do ficheiro
*/
void set_lugar(char *valor, char *linha, int top_scores[TOP]){
  int i;
  char arg[100];
  sscanf(linha, "%[^-]", arg);
  sscanf(arg, "%d", &i);
  sscanf(valor, "%d", &top_scores[TOP-i]);
}

/**
\brief Funcao que chama uma determinada funcao, dependendo do conteudo da linha
@param linha Linha que contem a informacao
@param top_scores Array onde sera colocado os scores lidos do ficheiro
*/
void ler_campo_score(char *linha, int top_scores[TOP]){
  struct{
		char *nome;
		void (*funcao)(char *valor, char *linha, int top_scores[TOP]);
	} campos[]={
		{"lugar", set_lugar},
		{NULL,NULL}
	};
	char campo[100];
	char resto[10240];
	sscanf(linha, "%[^:]: %[^\n]", campo, resto);

  int i = 0;

  while(campos[i].nome != NULL && strstr(campo, campos[i].nome) == 0) i++;

  if (campos[i].nome == NULL){
    fprintf(stderr, "campo %s nao existe\n", campo);
    exit(1);
  }
  return campos[i].funcao(resto, linha, top_scores);
}

/**
\brief Funcao que le o ficheiro para retirar os valores escritos neste
@param score Ficheiro que contem a informacao
@param filename Nome do ficheiro
@top_scores Array onde serao colocados os melhores scores
*/
void le_pontos(FILE *score, char *filename, int top_scores[TOP]){
  score = fopen(filename, "r");
  if (score == NULL){
    perror("nao consegui abrir o ficheiro");
    exit(1);
  }

  char linha[10240];
  while(fgets(linha, 10240, score) != NULL)
    ler_campo_score(linha, top_scores);
}
