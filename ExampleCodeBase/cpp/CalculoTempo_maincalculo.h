/*
	maincalculo.h
	------
	Este arquivo contem os includes de defines do arquivo main.c

*/
#include "CalculoTempo_map_op_prott.h"
#include <stdio.h>
#include <stdlib.h>
#include "CalculoTempo_busca_a.h"
#include <iostream>
#include <algorithm>
#include <omp.h>
#include <unistd.h>
#include <time.h>
//#include "node.cpp"


#define BILLION 1000000000L
#define FPS ((double)45.0)

int
main(int argc, char **argv);

void
encontra_caminhodungeon(Busca_a * busca, Vector2 ini, Vector2 fim,int**tile,int tam,double *global_time);
