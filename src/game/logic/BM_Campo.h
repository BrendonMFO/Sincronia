#ifndef _BM_LOGIC_CAMPO_
#define _BM_LOGIC_CAMPO_

#include <stdio.h>
#include <string.h>
#include "BM_Hexagono.h"

typedef struct BM_Campo_S
{
  int quantidade;
  BM_HEXAGONO *hexagonos;
} BM_Campo;

BM_Campo *BM_Campo_getCampo();

void BM_Campo_setCampo(char *_campo);

void BM_Campo_redefinir();

void BM_Campo_inicial(int player_pos);

#endif