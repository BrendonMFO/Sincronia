//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Allegro_eventos.h"
#include "BM_Allegro_eventos_mouse.h"

//==========================================================================
// Variaveis para controle de eventos
//==========================================================================
ALLEGRO_EVENT BM_Loop_evento;
ALLEGRO_TIMEOUT BM_Loop_timeout;
ALLEGRO_EVENT_QUEUE *BM_Loop_filaEventos;

//==========================================================================
// Prototipos
//==========================================================================
void BM_Eventos_executarFilaFuncoes();
void BM_Eventos_iniciarListenerEventos();
int BM_Eventos_janela(ALLEGRO_DISPLAY *_janela);

//==========================================================================
// Obter fila de eventos
//==========================================================================
ALLEGRO_EVENT_QUEUE *BM_Eventos_obter_fila()
{
	return BM_Loop_filaEventos;
}

//==========================================================================
// Iniciar eventos
//==========================================================================
int BM_Eventos_iniciar(ALLEGRO_DISPLAY *_janela)
{
	BM_Eventos_janela(_janela);
	BM_Eventos_iniciarListenerEventos();
	return 1;
}

//==========================================================================
// Iniciar fila de eventos da aplicação
//==========================================================================
int BM_Eventos_janela(ALLEGRO_DISPLAY *_janela)
{
	BM_Allegro_criar_eventos(&BM_Loop_filaEventos);
	al_register_event_source(BM_Loop_filaEventos, al_get_display_event_source(_janela));
	return 1;
}

//==========================================================================
// Iniciar variaveis responsaveis por escutar os eventos do jogo
//==========================================================================
void BM_Eventos_iniciarListenerEventos()
{
	al_init_timeout(&BM_Loop_timeout, 0.15);
	al_register_event_source(BM_Loop_filaEventos, al_get_keyboard_event_source());
	al_register_event_source(BM_Loop_filaEventos, al_get_mouse_event_source());
}

//==========================================================================
// Eventos do jogo
//==========================================================================
int BM_Eventos_processar()
{
	int tem_eventos = al_wait_for_event_until(BM_Loop_filaEventos, &BM_Loop_evento, &BM_Loop_timeout);
	if (tem_eventos && BM_Loop_evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		return FECHAR_JOGO;
	BM_Eventos_executarFilaFuncoes();
	return LOOP;
}

//==========================================================================
// Executar fila de funções
//==========================================================================
void BM_Eventos_executarFilaFuncoes()
{
	BM_EVENTOS_FUNCAO *aux, *aux2;

	if (BM_Eventos_obter_fila_funcao() == NULL)
		return;

	for (aux = BM_Eventos_obter_fila_funcao()->inicio; aux != NULL;)
	{
		aux->funcao(BM_Loop_evento, aux->parametro);

		if (aux->ativo != 0)
		{
			aux = aux->proximo;
			continue;
		}

		if (aux->proximo == NULL)
		{
			aux = NULL;
		}
		else
		{
			aux2 = aux->proximo;
			free(aux->parametro);
			free(aux);
			aux = aux2;
		}
	}
}
