//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Socket.h"
#include "BM_Core_Renders.h"
#include "BM_Core_Carregar.h"
#include "BM_Socket_events.h"
#include "BM_Recursos_Animacao.h"

//==========================================================================
// Prototipos
//==========================================================================
int BM_Core_carregar_recursos();
int BM_Core_carregar_campo();

//==========================================================================
// Carregar dados
//==========================================================================
int BM_Core_carregar()
{
	BM_Socket_connect();
	BM_Socket_events_init();
	return BM_Core_carregar_recursos() &&
		   BM_Core_carregar_campo() &&
		   BM_Player_iniciar(11) &&
		   BM_Oponente_iniciar(18);
}

//==========================================================================
// Carregar Recursos
//==========================================================================
int BM_Core_carregar_recursos()
{
	return BM_Allegro_iniciar() &&
		   BM_Recursos_carregar_recursos() &&
		   BM_Eventos_iniciar_fila_funcoes() &&
		   BM_Eventos_Mouse_iniciar_fila_mouse() &&
		   BM_Animacao_iniciar_fila() &&
		   BM_Render_iniciar_fila();
}

//==========================================================================
// Carregar informaçoes do campo
//==========================================================================
int BM_Core_carregar_campo()
{
	BM_Campo_setCampo(RESOURCE("Fases/Mapa_01.gf"));
	if (BM_Campo_getCampo() == NULL)
	{
		return 0;
	}
	return 1;
}
