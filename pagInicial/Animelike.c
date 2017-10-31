#include <stdio.h>
#include "cgi.h"
#include "images.h"

/**
@file Animelike.c
Ficheiro que contem a pagina inicial do jogo
*/

/**
\brief Gera uma pagina HTML para comecar o jogo
*/
int main(){
  START_HTML;
  HTML_HEAD(TITULO);
  printf("<audio src=http://localhost/images2.0/song.mp3 autoplay>\
Your browser does not support the audio element.\
</audio>");

printf("<style>\nbody {\nbackground-image: url(%sBackgrounds/extra.png);\nbackground-repeat: no-repeat;\n\
                                    background-size: cover;}\n</style>\n", IMAGE_PATH);
  START_SVG(1900,880);
  ABRIR_LINK("http://localhost/cgi-bin/game");
  printf("<image x=750 y=250 width=300 height=500 xlink:href = %sMisc/start.png />\n", IMAGE_PATH);
  FECHAR_LINK;

  COPYRIGHTS;
  STOP_SVG;

  return 0;
}
