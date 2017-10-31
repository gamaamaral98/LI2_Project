#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgi.h"
/**
@file escreve.c
Ficheiro para escrever os melhores scores num ficheiro
*/
/**
\brief Funcao que escreve num ficheiro os top scores
@param top_scores Array com os top_scores
*/
void escreve_pontos(int top_scores[TOP]){
  int i;
  char *nome = "score";
	char filename[1024];
	sprintf(filename, "/var/www/html/user/%s", nome);
	FILE *score = fopen(filename, "w");
  if (score == NULL){
    perror("nao consegui abrir o ficheiro para escrever \n");
    exit(1);
  }
  for (i = 1; i <= TOP; i++)
    fprintf(score, "%d-lugar: %d\n", i, top_scores[TOP-i]);
}
