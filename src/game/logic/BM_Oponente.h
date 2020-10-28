#ifndef _BM_LOGIC_PLAYER_IA_
#define _BM_LOGIC_PLAYER_IA_

#include "BM_Player.h"
#include "BM_Hexagono.h"

int BM_Oponente_iniciar(int _hexagonoAtual);

void BM_Oponente_iniciar_valores(int _hexagono);

BM_PLAYER *BM_Player_getOpponentPlayer();

void BM_Oponente_set_socket(int socket);

int BM_Oponente_get_socket();

void BM_Oponente_checar_tempo();

void BM_Oponente_set_hexagon(int hexagon);

void BM_Oponente_capture_hexagon(int hexagon, int element);

void BM_Oponente_executar_ataque(int _alvo);

#endif