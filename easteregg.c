#include <stdio.h>
#include "prototipos.h"
#include "cgi.h"
#include "images.h"
/**
@file easteregg.c
Funçoes que analisam o estado do easteregg: se foi desbloqueado e se vai ser imprimido
*/

/**
\brief Função que imprime o 'Easteregg'
@param e Estado atual do jogo
@param id_easter Imagem a ser selecionada do array de imagens dos eastereggs
* Apenas executa caso o jogador tenha
* encontrado o 'easteregg'
* (caso @code e.enc_easter = 1 @endcode)
*/
void print_easteregg(ESTADO e, int id_easter){
	if (e.enc_easter) {
		printf("<a target=_blank xlink:href=http://localhost/images2.0/Eastereggs/%s>\n", images_Easteregg[id_easter]);
		PRINT_IMAGE(14, 1, MISC, CLICK_EASTEREGG);
		FECHAR_LINK;
	}
}


/**
\brief Função que averigua se o jogador encontrou a surpresa
@param e Estado atual do jogo
@returns Estado com o parametro de "encontrou surpresa" a 1
*/
ESTADO enc_easteregg(ESTADO e){
		if (e.jog.coord.x == e.easteregg.x && e.jog.coord.y == e.easteregg.y){
			e.enc_easter = 1;
			e.jog.score += 50;
		}
		return e;
}
