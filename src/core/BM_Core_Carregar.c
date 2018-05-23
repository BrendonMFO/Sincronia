#include "BM_Core_Carregar.h"
#include "BM_Recursos_Animacao.h"
#include "BM_Core_Renders.h"

//==========================================================================
// Prototipos
//==========================================================================
int BM_CORE_carregar_recursos();
int BM_CORE_carregar_campo();

//==========================================================================
// Carregar dados
//==========================================================================
int BM_CORE_carregar()
{
	return BM_CORE_carregar_recursos() &&
		   BM_CORE_carregar_campo() &&
		   BM_Player_iniciar(0) &&
		   BM_Player_IA_iniciar(BM_Campo_getCampo()->quantidade - 1);
}

//==========================================================================
// Carregar Recursos
//==========================================================================
int BM_CORE_carregar_recursos()
{
	return BM_Allegro_iniciar() &&
		   BM_Recursos_carregar_recursos() &&
		   BM_Eventos_iniciar_fila_funcoes() &&
		   BM_Eventos_Mouse_iniciar_fila_mouse() &&
		   BM_Animacao_iniciar_fila() &&
		   BM_Render_iniciar_fila();
}

//==========================================================================
// Carregar informa��es do campo
//==========================================================================
int BM_CORE_carregar_campo()
{
	BM_Campo_setCampo(RESOURCE("Fases/Mapa_01.gf"));
	if (BM_Campo_getCampo() == NULL)
	{
		return ERRO;
	}
	return SUCESSO;
}
