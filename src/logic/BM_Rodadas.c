#include "BM_Rodadas.h"
#include "BM_Player.h"
#include "BM_Player_IA.h"
#include "BM_Recursos_Conteudo.h"
#include "BM_Recursos.h"

//==========================================================================
// Variaveis
//==========================================================================
int RODADAS_RESTANTES;

//==========================================================================
// Set Rodadas
//==========================================================================
void BM_Rodada_set(int _quantidade)
{
	RODADAS_RESTANTES = _quantidade;
}

//==========================================================================
// Get Rodadas restantes
//==========================================================================
int BM_Rodada_get_restantes()
{
	return RODADAS_RESTANTES;
}

//==========================================================================
// Avançar rodadas
//==========================================================================
void BM_Rodada_avancar()
{
	RODADAS_RESTANTES--;
	BM_Player_checar_tempo();
	BM_IA_checar_tempo();
}