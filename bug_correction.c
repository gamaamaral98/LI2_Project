/**
@file bug_correction.c
* Ficheiro que contem funcoes de debugg do jogo
*/

/**
\brief Imprime no ecra as distancias de cada casa em relacao ao jogador
*/
void print_teste(){
	int l, c;
	for (l = 0; l < TAM; l++)
    for (c = 0; c < TAM; c++)
			printf("<text x=%d y=%d fill=red>%d</text>\n", c*SCALE, l*SCALE, matriz[l][c]);
}
