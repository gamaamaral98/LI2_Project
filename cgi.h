#ifndef ___CGI_H___
#define ___CGI_H___

/**
@file cgi.h
* Macros necessários para gerar CGIs
*/

#include <stdio.h>

/**
\brief Caminho para as imagens
*/
#define IMAGE_PATH          "http://localhost/images2.0/"

/**
\brief Atribuição de um título
*/
#define TITULO                "Anime RogueLike"

/**
\brief Macro para começar HTML
*/
#define START_HTML            printf("Content-type: text/html\n\n")

/**
\brief Macro para colocar um titulo na pagina
@param TITULO Titulo desejado
*/
#define HTML_OPEN_HEAD(TITULO)     printf("<head>\n<title>\n%s\n</title>\n", TITULO)
#define HTML_CLOSE_HEAD            printf("</head>\n")

/**
\brief Macro para adicionar uma imagem de backgroud
@param ficheiro Imagem a colocar
*/
#define HTML_BG(ficheiro)   printf("<style>\nbody {\nbackground-image: url(%sBackgrounds/%s);\nbackground-repeat: no-repeat;\n\
                                    background-size: cover;}\n</style>\n", IMAGE_PATH, images[ficheiro])

/**
\brief Macro para abrir o svg
1800 - 880
@param tamx O comprimento do svg
@param tamy A largura do svg
*/
#define START_SVG(tamx, tamy)   printf("<svg width=%d height=%d>\n", tamx, tamy)

/**
\brief Macro para fechar o svg
*/
#define STOP_SVG              printf("</svg>\n")

/**
\brief Macro para criar uma Imagem
@param x Coordenada x
@param y Coordenada y
@param ficheiro Imagem a ser colocada (indexada dentro do array images)
* O 'x' é somado a uma constante "CENTRAR" para
* a imagem ficar centrada no ecrã
*/
#define PRINT_IMAGE(x, y, path, ficheiro)           printf("<image x=%d y=%d width=%d height=%d xlink:href = %s%s%s />\n", x*SCALE, y*SCALE, SCALE, SCALE, IMAGE_PATH, path, images[ficheiro])

/**
\brief Macro para abrir um link
@param link O caminho para o link
*/
#define ABRIR_LINK(link)					printf("<a xlink:href=%s>\n", link)

/**
\brief Macro para fechar o link
*/
#define FECHAR_LINK							printf("</a>\n")

/**
\brief Macro para apresentar os 'Developers' do jogo
*/
#define COPYRIGHTS        printf("<text x=0 y=866 fill = white font-size = 29>\nCopyrights: Filipe Monteiro, Joao Amaral, Miguel Arrepia\n</text>\n")

/**
\brief Macro que imprime os quadrados da tabela na tela.
*/
#define TABLE_RECTS         printf("<rect x=1500 y=0 fill=white stroke-width=4 stroke=black width=400 height=65 />\n\
                                    <rect x=1500 y=65 fill=white stroke-width=4 stroke=black width=200 height=80 />\n\
                                    <rect x=1700 y=65 fill=white stroke-width=4 stroke=black width=200 height=80 />\n\
                                    <rect x=1500 y=145 fill=white stroke-width=4 stroke=black width=200 height=80 />\n\
                                    <rect x=1700 y=145 fill=white stroke-width=4 stroke=black width=200 height=80 />\n\
                                    <rect x=1500 y=225 fill=white stroke-width=4 stroke=black width=200 height=80 />\n\
                                    <rect x=1700 y=225 fill=white stroke-width=4 stroke=black width=200 height=80 />\n\
                                    <rect x=1500 y=305 fill=white stroke-width=4 stroke=black width=200 height=100 />\n\
                                    <rect x=1700 y=305 fill=white stroke-width=4 stroke=black width=200 height=100 />\n")

/**
\brief Macro que imprime o texto dentro da tabela.
@param e Estado onde está armazenada informação a ser usada por esta macro.
*/
#define TABLE_TEXT(e)          printf("<text x=1650 y=45 fill=black font-size=30>\nNivel %d\n</text>\n\
                                       <text x=1550 y=120 fill=black font-size=30>\nSCORE\n</text>\n\
                                       <text x=1750 y=120 fill=black font-size=30>\n%d\n</text>\n\
                                       <text x=1503 y=200 fill=black font-size=25>\nInim.Derrotados\n</text>\n\
                                       <text x=1750 y=200 fill=black font-size=30>\n%d\n</text>\n\
                                       <text x=1500 y=275 fill=black font-size=25>\nBoss.Derrotados\n</text>\n\
                                       <text x=1750 y=275 fill=black font-size=30>\n...\n</text>\n\
                                       <text x=1750 y=355 fill=black font-size=30>\n%d\n</text>\n\
                                       <image x=1550 y=315 width=100 height=80 xlink:href = http://localhost/images2.0/Misc/energy.png />\n"\
                                                          , e.nivel, e.jog.score, e.jog.ini_derrotados, e.jog.stamina)

/**
\brief Macro que imprime uma imagem para pedir ajuda.
*/
#define HELP                       printf("<image x=850 y=0 width=150 height=150 xlink:href = %sMisc/duvida.png />\n", IMAGE_PATH)

/**
\brief Macro que imprime uma imagem para a saída.
*/
#define PRINT_SAIDA               printf("<image x=1800 y=400 width=100 height=100 xlink:href = %sMisc/restart.png />\n", IMAGE_PATH)

/**
\brief Tamanho utilizado quando queremos gerar algo de grande número.
*/
#define MAX_BUFFER	10240

/**
\brief Tamanho do mapa.
*/
#define TAM         12

/**
\brief Escala das imagens no mapa.
*/
#define SCALE       70

/**
\brief Coordenada x das imagem da 'vida'.
*/
#define VD_X        13

/**
\brief Coordenada y das imagem da 'vida'.
*/
#define VD_Y        11

/**
\brief Máximo de scores guardados.
*/
#define TOP         10

#endif
