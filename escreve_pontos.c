#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgi.h"
/**
@file escreve_pontos.c
Escreve os pontos do jogador num ficheiro
*/

/**
\brief Escreve o score do jogador no ficheiro(a cada ação)
@param score Ficheiro onde irá escrever
@param filename Nome do ficheiro onde se ira escrever
@param myscore Score atual do jogador
@returns Score do jogador guardado no ficheiro
*/
void escreve_pontos(FILE *score, char *filename, int myscore){
  score = fopen(filename, "w");
  if (score == NULL){
    perror("nao consegui abrir o ficheiro para escrever \n");
    exit(1);
  }
  fprintf(score, "My Score: %d\n", myscore);
}
