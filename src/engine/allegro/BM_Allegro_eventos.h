#ifndef _BM_ALLEGRO_EVENTOS_
#define _BM_ALLEGRO_EVENTOS_

#include "BM_Allegro.h"
#include "BM_Allegro_eventos_funcoes.h"

//==========================================================================
// ENUM de estados dos eventos
//==========================================================================
enum BM_EVENTOS_DISPARADOS
{
	FECHAR_JOGO = 2,
	LOOP = 3
};

//==========================================================================
// Obter fila de eventos
//==========================================================================
ALLEGRO_EVENT_QUEUE *BM_Eventos_obter_fila();

//==========================================================================
// Iniciar eventos
//==========================================================================
int BM_Eventos_iniciar(ALLEGRO_DISPLAY *_janela);

//==========================================================================
// Eventos do jogo
//==========================================================================
int BM_Eventos_processar();

#endif