#ifndef _BM_ALLEGRO_EVENTOS_MOUSE_
#define _BM_ALLEGRO_EVENTOS_MOUSE_

#include "BM_Allegro.h"

//==========================================================================
// Definir novos tipos
//==========================================================================
typedef void (*BM_MOUSE_FUNCAO)(int, ...);

//==========================================================================
// Estrutura de dados para os eventos do mouse
//==========================================================================
typedef struct BM_EVENTO_MOUSE_S
{
	int inicial_X;
	int inicial_Y;
	int final_X;
	int final_Y;
	BM_MOUSE_FUNCAO funcao;
	void *opcional;
	struct BM_EVENTO_MOUSE_S *anterior;
	struct BM_EVENTO_MOUSE_S *proximo;
} BM_EVENTO_MOUSE;

//==========================================================================
// Fila de eventos do mouse
//==========================================================================
typedef struct BM_EVENTO_MOUSE_FILA_S
{
	BM_EVENTO_MOUSE *inicio;
	BM_EVENTO_MOUSE *fim;
} BM_EVENTO_MOUSE_FILA;

//==========================================================================
// Iniciar fila de eventos
//==========================================================================
int BM_Eventos_Mouse_iniciar_fila_mouse();

//==========================================================================
// Adicionar funcao na pilha
//==========================================================================
int BM_Eventos_Mouse_adicionar(BM_MOUSE_FUNCAO _funcao, int _iX, int _iY, int _fX, int _fY, void *_opcional);

//==========================================================================
// Adicionar funcao na pilha
//==========================================================================
void BM_Eventos_Mouse_remover(int _posicaoX, int _posicaoY, int _finalX, int _finalY);

//==========================================================================
// Obter fila de eventos
//==========================================================================
BM_EVENTO_MOUSE_FILA *BM_Eventos_Mouse_obter_fila_funcao();

//==========================================================================
// Processar fila
//==========================================================================
BM_EVENTO_MOUSE *BM_Eventos_Mouse_processar(int _clickX, int _clickY);

#endif