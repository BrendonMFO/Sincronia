#ifndef _BM_LOGIC_PLAYER_
#define _BM_LOGIC_PLAYER_

#include "BM_Elemento.h"

//==========================================================================
// Estrutura de dados de um player
//==========================================================================
typedef struct BM_PLAYER_S
{
	int quantidadeTerritorio;
	int hexagonoAtual;
	BM_ELEMENTOS elementosDisponivel;
	BM_ELEMENTOS elementosTempo;
} BM_PLAYER;

//==========================================================================
// Iniciar player
//==========================================================================
int BM_Player_iniciar(int _hexagonoInicialJogador);

//==========================================================================
// Mover player
//==========================================================================
void BM_Player_mover(BM_PLAYER *_player, int _mouseX, int _mouseY);

//==========================================================================
// Definir valores iniciais
//==========================================================================
void BM_Player_iniciar_valores(int _hexagono);

//==========================================================================
// Get jogador
//==========================================================================
BM_PLAYER *BM_Player_getJogador();

//==========================================================================
// Checar elementos
//==========================================================================
void BM_Player_checar_elemento(int _elemento);

//==========================================================================
// Checar tempo elemento
//==========================================================================
void BM_Player_checar_tempo();

//==========================================================================
// Checar se o elemento esta disponivel
//==========================================================================
int BM_Player_disponibilidade_elemento(int _elemento);

#endif