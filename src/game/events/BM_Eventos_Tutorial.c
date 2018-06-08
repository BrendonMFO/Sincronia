//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Campo.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Hexagono.h"
#include "BM_Tutorial.h"
#include "BM_Core_Eventos.h"
#include "BM_Allegro_eventos.h"

//==========================================================================
// Prototipos
//==========================================================================
void BM_Eventos_Tutorial_avancar();
void BM_Eventos_Tutorial_iniciar_jogo();
void BM_Eventos_Tutorial(ALLEGRO_EVENT, void *);

/**
 * @brief 
 * - Adicionar eventos na lista de funções e renderizações relacionados aos
 *   tutoriais
 */
void BM_Eventos_Tutorial_registrar()
{
	BM_Eventos_adicionar_funcao(BM_Eventos_Tutorial, NULL);
}

/**
 * @brief 
 * - Eventos disparados na tela de tutorial
 */
void BM_Eventos_Tutorial(ALLEGRO_EVENT event, void *_parametro)
{
	switch (event.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (event.keyboard.keycode)
		{
		case ALLEGRO_KEY_I:
			return BM_Eventos_Tutorial_iniciar_jogo();
		case ALLEGRO_KEY_ENTER:
			return BM_Eventos_Tutorial_avancar();
		}
	}
}

/**
 * @brief 
 * - Finalizar tutorial e iniciar os procedimentos do jogo
 */
void BM_Eventos_Tutorial_iniciar_jogo()
{
	BM_Render_remover_funcao(BM_Render_tutorial);
	BM_Eventos_Funcoes_remover(BM_Eventos_Tutorial);
	BM_Eventos_Partida_procurar();
}

/**
 * @brief 
 * - Avançar tutorial 
 */
void BM_Eventos_Tutorial_avancar()
{
	if (BM_Render_obter_tutorial() == 9)
		BM_Eventos_Tutorial_iniciar_jogo();
	else
		BM_Render_avancar_tutorial();
}