#include <stdio.h>
#include "cgi.h"
/**
@file duvida.c
Pagina HTML criada onde terá as regras do jogo, explicação de dúvidas.
*/

/**
\brief Página HTML onde tem as regras do jogo.
* Estão aqui presentes a vida, armadura, inimigos e outros parâmetros importantes
* para que quem esteja a jogar perceba como funciona o jogo.
*/
int main(){
  START_HTML;
  HTML_OPEN_HEAD("Regras do Animelike");
  printf("<style>\ntd img {\
                    max-width:50%;\
                    height:auto;\
                   }\n\
                   table {\
                    position: absolute;\
                    left: 650px;\
                    top: 10px;\
                   }\
                    table, th, td {\
                    border: 1px solid black;\
                    padding: 5px;\
                    text-align: center;\
                    border-collapse: collapse;\
                   }\
                    table.center {\
                    margin-left:auto;\
                    margin-right:auto;\
                   }\
          </style>\n");
  HTML_CLOSE_HEAD;
  printf("<style>\nbody {\nbackground-image: url(%sMisc/teste.jpg);\nbackground-repeat: no-repeat;\n\
                                      background-size: cover;}\n</style>\n", IMAGE_PATH);

  printf("<table bgcolor=#FFFFFF class=center width=600 border=1 cellpadding=5>\n");
  printf("<tr>\n<td align=center valign=center>\n<img src=http://localhost/images2.0/Misc/Vida.png />\
          </td>\n<td align=center valign=center>\nRepresenta a percentagem de vida do jogador.\n</td>\n</tr>\n");
  printf("<tr>\n<td align=center valign=center>\n<img src=http://localhost/images2.0/Misc/armor.png />\
         </td>\n<td align=center valign=center>\nRepresenta a percentagem de armadura do jogador.\n</td>\n</tr>\n");
  printf("<tr>\n<td align=center valign=center>\n<img src=http://localhost/images2.0/Misc/energy.png />\
         </td>\n<td align=center valign=center>\nRepresenta a stamina do jogador.\n</td>\n</tr>\n");
  printf("<tr>\n<td align=center valign=center>\n<img src=http://localhost/images2.0/Misc/genki_dama.png />\
          </td>\n<td align=center valign=center>\nApenas aparece se estiver disponivel o seu ataque especial.\
         Precisa de 4 stamina para ser executado e consiste num 'beam' de raio 5, que mata tudo nessa direcaoo, ate mesmo paredes.\
         Se encontrar uma parede, destroi esta e nao avanca mais. Mas cada fez que esta habilidade e usada, o jogador\
         permanece quieto por 2 jogadas.\n</td>\n</tr>\n");
 printf("<tr>\n<td align=center valign=center>\n<img src=http://localhost/images2.0/InimigosLvl1/Inimigolvl1.png />\
        </td>\n<td align=center valign=center>\nInimigo mais fraco. Existe sempre em maior abundancia.\n</td>\n</tr>\n");
 printf("<tr>\n<td align=center valign=center>\n<img src=http://localhost/images2.0/InimigosLvl3/vegeta.png />\
        </td>\n<td align=center valign=center>\nInimigo que ataca ao longe. So ataca se estiver dentro de um raio de 4 casa\
        do jogador. Senao procura uma posicao estrategica para atacar.\n</td>\n</tr>\n");
 printf("<tr>\n<td align=center valign=center>\n<img src=http://localhost/images2.0/InimigosLvl5/hitto.png />\
        </td>\n<td align=center valign=center>\nInimigo raro, que so mexe em caso de extrema necessidade. Melhor nao acordar\
        o bicho.\n</td>\n</tr>\n");
}
