/**
@file testes.c
* Bonus que nao chegaram a fase final do trabalho.
*/

/**
\brief Imprime no ecra o field of view.
*/
void print_fieldOfVision(){
	int c, l;
	for (l = 0; l < TAM; l++)
		for (c = 0; c < TAM; c++){
			printf("<rect x=%d y=%d width=%d height=%d fill=black fill-opacity=%d />\n", c*SCALE, l*SCALE, SCALE, SCALE, fieldVision[l][c]);
		}
}

int fieldOfVision_casa_aux(ESTADO e, int novox, int novoy, int r, int diag){
  if (!posicao_valida(novox, novoy)) return 0;

  if (!tem_obstaculo(e, novox, novoy) && (novox == e.jog.coord.x || novoy == e.jog.coord.y || novox + novoy == diag || novox + novoy == diag + 2)){
      fieldVision[novoy][novox] = 0;
      if (r > 0) return 1;
  }
  return 0;
}

void fieldOfVision_casa(ESTADO *e, int x, int y, int r){
  int dx, dy;
  int novox, novoy;
  int diag;

  fieldVision[y][x] = 0; // casa visivel

  for (dy = -1; dy < 2; dy++)
    for (dx = -1; dx < 2; dx++){
      novox = x + dx;
      novoy = y + dy;
      diag = e->jog.coord.x + e->jog.coord.y;
      if(fieldOfVision_casa_aux(*e, novox, novoy, r, diag))
        fieldOfVision_casa(e, novox, novoy, r-1);
    }
}

void fieldOfVision(ESTADO e){
  int l, c;
  for (l = 0; l < TAM; l++)
    for (c = 0; c < TAM; c++)
      fieldVision[l][c] = 1; //casa tapada

  fieldOfVision_casa(&e, e.jog.coord.x, e.jog.coord.y, 5); // r=5 (raio de visao)
}
