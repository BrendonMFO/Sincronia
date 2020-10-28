#include "BM_Player.h"
#include "BM_Rodadas.h"
#include "BM_Oponente.h"
#include "BM_Recursos.h"
#include "BM_Recursos_Conteudo.h"

static int RODADAS_RESTANTES;

void BM_Rodada_set(int _quantidade)
{
  RODADAS_RESTANTES = _quantidade;
}

int BM_Rodada_get_restantes()
{
  return RODADAS_RESTANTES;
}

void BM_Rodada_avancar()
{
  RODADAS_RESTANTES--;
  BM_Player_checar_tempo();
  BM_Oponente_checar_tempo();
}