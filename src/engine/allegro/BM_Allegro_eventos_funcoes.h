#ifndef _BM_ALLEGRO_FUNCOES_
#define _BM_ALLEGRO_FUNCOES_

#include "BM_Allegro_eventos.h"

//==========================================================================
// Typedef's
//==========================================================================
typedef void (*BM_EVENTO_FUNCAO)(ALLEGRO_EVENT, void *);

//==========================================================================
// Estrutura de dados das funções que devem ser associadas aos eventos
//==========================================================================
typedef struct BM_EVENTOS_FUNCAO_S
{
	struct BM_EVENTOS_FUNCAO_S *anterior;
	int ativo;
	void *parametro;
	BM_EVENTO_FUNCAO funcao;
	struct BM_EVENTOS_FUNCAO_S *proximo;
} BM_EVENTOS_FUNCAO;

//==========================================================================
// Fila de funções dos eventos
//==========================================================================
typedef struct BM_EVENTOS_FILA_S
{
	BM_EVENTOS_FUNCAO *inicio;
	BM_EVENTOS_FUNCAO *fim;
} BM_EVENTOS_FILA;

//==========================================================================
// Iniciar fila de eventos
//==========================================================================
int BM_Eventos_iniciar_fila_funcoes();

//==========================================================================
// Adicionar funcao na fila
//==========================================================================
int BM_Eventos_adicionar_funcao(BM_EVENTO_FUNCAO _funcao, void *_parametro);

//==========================================================================
// Adicionar funcao na fila
//==========================================================================
void BM_Eventos_Funcoes_remover(BM_EVENTO_FUNCAO _funcao);

//==========================================================================
// Obter fila de eventos
//==========================================================================
BM_EVENTOS_FILA *BM_Eventos_obter_fila_funcao();

#endif