#include "cgi.h"
#include <stdio.h>
#include <stdlib.h>

/**
@file gameover.c
Ficheiro para criar uma pagina quando o jogador for derrotado
*/

/**
\brief Prototipos de funçoes
*/
void escreve_pontos(int top_scores[TOP]);
void le_pontos(FILE *score, char *filename, int top_scores[TOP]);

/**
\brief Imprime uma tabela no ecra com os scores
@param myscore Score do jogador
@param top_scores Array com o os melhores scores
*/
void print_table(int myscore, int top_scores[TOP]){
	int i;
	printf("<head>\
<style>\
table {\
	position: absolute;\
	left: 650px;\
	top: 350px;\
}\
table, th, td {\
    border: 1px solid black;\
		padding: 5px;\
		text-align: center;\
		border-collapse: collapse;}\
		\
table.center {\
  margin-left:auto;\
  margin-right:auto;\
}\
img {\
	position: absolute;\
	top:300px;\
	left: 50px;\
}\
</style>\
</head>\
<body>\
<table bgcolor=#FFFFFF class=center width=600 >\
  <tr>\
    <th>Lugar</th>\
    <th>Score</th> \
  </tr>\n");
	for (i = 1; i <= TOP; i++)
		printf("<tr>\
		    <td>%d Pontos</td>\
		    <td>%d Pontos</td>\
		  </tr>\n", i, top_scores[TOP-i]);
	printf("<tr>\n<td>\nMy Score\n</td>\n<td>\n%d Pontos\n</td>\n</tr>\n", myscore);
	printf("</table>\n</body>\n");
}

/**
\brief Imprime no era um botao para recomecar o jogo
@param x Coordenada x no ecra onde sera imprimido
@param y Coordenada y no ecra onde sera imprimido
*/
void print_restart(int x, int y){
		ABRIR_LINK("http://localhost/cgi-bin/game?novo");
		printf("<image x=%d y=%d width=%d height=%d xlink:href = %sMisc/again.png />\n", x*SCALE, y*SCALE, 350, 350, IMAGE_PATH);
		FECHAR_LINK;
}

/**
\brief Funcao que insere o score do jogador, se puder, dentro do array de melhores scores
@param myscore Score do jogador
@param top_scores Array com os melhores scores
*/
void insere_myscore(int myscore, int top_scores[TOP]){
	int i, j;
	for (i = 0; i < TOP; i++)
		if (top_scores[i] > myscore) {top_scores[i-1] = myscore;break;}

	if (i == TOP && top_scores[i-1] < myscore){
			for (j = 0; j < TOP; j++){
				top_scores[j] = top_scores[j+1];
			}
			top_scores[i-1] = myscore;
	}
}

/**
\brief Organiza os melhores scores
@param top_scores Array com os melhores scores
*/
void organiza_score(int top_scores[TOP]){
	int i, j;
	int tmp;
	for (j = 0; j < TOP; j++){
		for (i = 0; i < TOP; i++){
			if (top_scores[i] > top_scores[i+1]){
				tmp = top_scores[i+1];
				top_scores[i+1] =  top_scores[i];
				top_scores[i] = tmp;
			}
		}
	}
}

/**
\brief Funcao que le o ficheiro dos melhores scores
@param top_scores Array onde serao colocados os melhores scores, lidos do ficheiro
*/
void ler_score(int top_scores[TOP]){
	char *nome = "score";
	char filename[1024];
	sprintf(filename, "/var/www/html/user/%s", nome);

	FILE *score = fopen(filename, "r");

	if (score == NULL){
		perror("nao consegui abrir o ficheiro SCORE INICIO\n");
		exit(1);
	} /*ver se abriu*/

	le_pontos(score, filename, top_scores);
}

/**
\brief Funcao que le o score final do jogador, do ficheiro
@param myscore Apontador para a variavel que contem o score final do jogador
*/
void ler_myscore(int *myscore){
	char *nome = "myscore";
	char filename[1024];
	sprintf(filename, "/var/www/html/user/%s", nome);
	FILE *score = fopen(filename, "r");
	if (score == NULL){
		perror("nao consegui abrir o ficheiro MYSCORE INICIO\n");
		exit(1);
	} /*ver se abriu*/

	char linha[10240];
	char number[100];
	fgets(linha, 10240, score);
	sscanf(linha, "%*[^:]: %[^\n]", number);
	sscanf(number, "%d", myscore);
}

/**
\brief Funcao que gera uma pagina HTML para acabar o jogo
* Contem uma tabela com os melhores scores e o proprio score.
*/
int main(){
	int myscore;
	int top_scores[TOP];
	ler_myscore(&myscore);
	ler_score(top_scores);

	organiza_score(top_scores);

	insere_myscore(myscore, top_scores);
	escreve_pontos(top_scores);

  START_HTML;
  HTML_HEAD("Gameover");
  printf("<style>\nbody {\nbackground-image: url(%sMisc/ending.png);\nbackground-repeat: no-repeat;\n\
                                      background-size: cover;}\n</style>\n", IMAGE_PATH);
	print_table(myscore, top_scores);
	printf("<img src=%sMisc/looser.gif width=500 height=400> \n", IMAGE_PATH); // trocar o gif maybe? xD
	printf("<audio src=http://localhost/images2.0/dead.mp3 autoplay >\
Your browser does not support the audio element.\
</audio>\n<body>\n");
  START_SVG(1900,800);
  print_restart(18, 4);

}
