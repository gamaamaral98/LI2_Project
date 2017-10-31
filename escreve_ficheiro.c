#include <stdio.h>
#include <stdlib.h>
#include "estado.h"
#include "prototipos.h"
#include "cgi.h"
#include <string.h>

#define str(s)  #s
#define int_field(fich, var, campo)  fprintf(fich, str(campo) ": %d\n", e.campo)
#define float_field(fich, var, campo)  fprintf(fich, str(campo) ": %f\n", e.campo)
#define field_vazio(state)   fprintf(state, "\n")

/** 
@file escreve_ficheiro.c
Ficheiro que contém todas as funções responsáveis por escrever o ficheiro em texto.
*/

/**
\brief Escreve os dados dos obstáculos no ficheiro
@param me Apontador para o estado, para buscar os valores
@param state Ficheiro onde irá escrever
@returns Dados dos inimigos tipo 3 guardados no ficheiro
*/
void escreve_obstaculos(ESTADO *me, FILE *state){
  int i;
  char string[1024];
  ESTADO e = *me;
  for (i = 0; i < e.num_obstaculos; i++){
    sprintf(string, "obstaculo[%d].coord.x: ", i);
    fprintf(state, "%s%d\n", string, e.obstaculo[i].coord.x);
    sprintf(string, "obstaculo[%d].coord.y: ", i);
    fprintf(state, "%s%d\n", string, e.obstaculo[i].coord.y);
    sprintf(string, "obstaculo[%d].vida: ", i);
    fprintf(state, "%s%d\n", string, e.obstaculo[i].vida);
  }
}

/**
\brief Escreve os dados dos inimigos tipo 1 no ficheiro
@param me Apontador para o estado, para buscar os valores
@param state Ficheiro onde irá escrever
@returns Dados dos inimigos tipo 1 guardados no ficheiro
*/
void escreve_inimigos1(ESTADO *me, FILE *state){
  int i;
  int tipo = 0;
  char string[1024];
  ESTADO e = *me;
  for (i = 0; i < e.num_inimigos1; i++){
    sprintf(string, "inimigo[%d][%d].coord.x: ", tipo, i);
    fprintf(state, "%s%d\n", string, e.inimigo[tipo][i].coord.x);
    sprintf(string, "inimigo[%d][%d].coord.y: ", tipo, i);
    fprintf(state, "%s%d\n", string, e.inimigo[tipo][i].coord.y);
    sprintf(string, "inimigo[%d][%d].vida: ", tipo, i);
    fprintf(state, "%s%f\n", string, e.inimigo[tipo][i].vida);
    sprintf(string, "inimigo[%d][%d].ataque: ", tipo, i);
    fprintf(state, "%s%f\n", string, e.inimigo[tipo][i].ataque);
  }
}

/**
\brief Escreve os dados dos inimigos tipo 2 no ficheiro
@param me Apontador para o estado, para buscar os valores
@param state Ficheiro onde irá escrever
@returns Dados dos inimigos tipo 2 guardados no ficheiro
*/
void escreve_inimigos2(ESTADO *me, FILE *state){
  int i;
  int tipo = 1;
  char string[1024];
  ESTADO e = *me;
  for (i = 0; i < e.num_inimigos2; i++){
    sprintf(string, "inimigo[%d][%d].coord.x: ", tipo, i);
    fprintf(state, "%s%d\n", string, e.inimigo[tipo][i].coord.x);
    sprintf(string, "inimigo[%d][%d].coord.y: ", tipo, i);
    fprintf(state, "%s%d\n", string, e.inimigo[tipo][i].coord.y);
    sprintf(string, "inimigo[%d][%d].vida: ", tipo, i);
    fprintf(state, "%s%f\n", string, e.inimigo[tipo][i].vida);
    sprintf(string, "inimigo[%d][%d].ataque: ", tipo, i);
    fprintf(state, "%s%f\n", string, e.inimigo[tipo][i].ataque);
  }
}

/**
\brief Escreve os dados dos inimigos tipo 3 no ficheiro
@param me Apontador para o estado, para buscar os valores
@param state Ficheiro onde irá escrever
@returns Dados dos inimigos tipo 3 guardados no ficheiro
*/
void escreve_inimigos3(ESTADO *me, FILE *state){
  int i;
  int tipo = 2;
  char string[1024];
  ESTADO e = *me;
  for (i = 0; i < e.num_inimigos3; i++){
    sprintf(string, "inimigo[%d][%d].coord.x: ", tipo, i);
    fprintf(state, "%s%d\n", string, e.inimigo[tipo][i].coord.x);
    sprintf(string, "inimigo[%d][%d].coord.y: ", tipo, i);
    fprintf(state, "%s%d\n", string, e.inimigo[tipo][i].coord.y);
    sprintf(string, "inimigo[%d][%d].vida: ", tipo, i);
    fprintf(state, "%s%f\n", string, e.inimigo[tipo][i].vida);
    sprintf(string, "inimigo[%d][%d].ataque: ", tipo, i);
    fprintf(state, "%s%f\n", string, e.inimigo[tipo][i].ataque);
  }
}

void escreve_baus(ESTADO e, FILE *state){
  int i;
  char string[1024];
  for (i = 0; i < e.num_baus; i++){
    sprintf(string, "bau[%d].coord.x: ", i);
    fprintf(state, "%s%d\n", string, e.bau[i].coord.x);
    sprintf(string, "bau[%d].coord.y: ", i);
    fprintf(state, "%s%d\n", string, e.bau[i].coord.y);
    sprintf(string, "bau[%d].content: ", i);
    fprintf(state, "%s%d\n", string, e.bau[i].content);
  }
}

/**
\brief Funçao que escreve os elementos do estado num ficheiro.
@param state Ficheiro onde se irá escrever
@param e Estado atual do jogo
@param filename Nome do ficheiro
@returns O ficheiro passa a ter os dados do estado
*/
void escreve_ficheiro(FILE *state, ESTADO e, char *filename){
  state = fopen(filename, "w");
  if (state == NULL){
    perror("nao consegui abrir o ficheiro para escrever \n");
    exit(1);
  }
  //int_field(state, e, ajuda_clicada);
  int_field(state, e, num_baus);
  escreve_baus(e, state);
  int_field(state, e, enc_easter);
  int_field(state, e, nivel);
  int_field(state, e, jog.coord.x);
  int_field(state, e, jog.coord.y);
  float_field(state, e, jog.n_vidas);
  float_field(state, e, jog.ataque);
  float_field(state, e, jog.armadura);
  int_field(state, e, jog.stamina);
  int_field(state, e, jog.score);
  int_field(state, e, jog.beam);
  int_field(state, e, jog.ini_derrotados);
  int_field(state, e, saida.x);
  int_field(state, e, saida.y);
  int_field(state, e, easteregg.x);
  int_field(state, e, easteregg.y);
  int_field(state, e, num_inimigos1);
  int_field(state, e, num_inimigos2);
  int_field(state, e, num_inimigos3);
  escreve_inimigos1(&e, state);
  escreve_inimigos2(&e, state);
  escreve_inimigos3(&e, state);
  int_field(state, e, num_obstaculos);
  escreve_obstaculos(&e, state);
  fclose(state);
}
