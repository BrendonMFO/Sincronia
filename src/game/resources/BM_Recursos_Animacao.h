//======================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//======================================================================

#ifndef _BM_RESOURCES_ANIMACAO_
#define _BM_RESOURCES_ANIMACAO_

#include "BM_Recursos_Conteudo.h"

//==========================================================================
// Constantes
//==========================================================================
#define SIM 1
#define NAO 2

//==========================================================================
// Estrutura de dados das animações pendentes
//==========================================================================
typedef struct BM_ANIMACAO_S
{
	BM_SPRITES *sprite;
	int frameAtualLinha;
	int frameAtualColuna;
	int render;
	int destinoW;
	int destinoH;
	int destinoX;
	int destinoY;
	int tempoAtualizacao;
	int tempoAtual;
	int finalizado;
	struct BM_ANIMACAO_S *anterior;
	struct BM_ANIMACAO_S *proximo;
} BM_ANIMACAO;

//==========================================================================
// Lista de animações pendentes
//==========================================================================
typedef struct BM_ANIMACAO_FILA_S
{
	BM_ANIMACAO *inicio;
	BM_ANIMACAO *fim;
} BM_ANIMACAO_FILA;

//==========================================================================
// Obter fila de animações pendentes
//==========================================================================
BM_ANIMACAO_FILA *BM_Animacao_obter_fila();

//==========================================================================
// Iniciar fila
//==========================================================================
int BM_Animacao_iniciar_fila();

//==========================================================================
// Adicionar animação
//==========================================================================
int BM_Animacao_adicionar(BM_SPRITES *_sprite, int _renderW, int _renderH, int _renderX, int _renderY, double _tempo);

//==========================================================================
// Remover animação
//==========================================================================
void BM_Animacao_remover(BM_ANIMACAO *_animacao);

//==========================================================================
// Avançar animacao
//==========================================================================
void BM_Animacao_avancar(BM_ANIMACAO *_animacao);

#endif