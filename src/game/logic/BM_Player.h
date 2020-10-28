#ifndef _BM_LOGIC_PLAYER_
#define _BM_LOGIC_PLAYER_

#include "BM_Hexagono.h"
#include "BM_Elemento.h"

typedef struct BM_PLAYER_S
{
  int quantidadeTerritorio;
  int hexagonoAtual;
  BM_ELEMENTOS elementosDisponivel;
  BM_ELEMENTOS elementosTempo;
} BM_PLAYER;

int BM_Player_iniciar(int _hexagonoInicialJogador);

BM_HEXAGONO *BM_Player_mover(BM_PLAYER *_player, int _mouseX, int _mouseY);

void BM_Player_iniciar_valores(int _hexagono);

BM_PLAYER *BM_Player_getJogador();

long long BM_Player_getId();

void BM_Player_setId(long long id);

void BM_Player_checar_elemento(int _elemento);

void BM_Player_checar_tempo();

int BM_Player_disponibilidade_elemento(int _elemento);

#endif