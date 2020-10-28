#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Oponente.h"
#include "BM_Core_Renders.h"
#include "BM_Communication.h"
#include "BM_Socket_events.h"
#include "BM_Socket_structs.h"
#include "BM_Communication_Send.h"
#include "BM_Communication_Receive.h"

void BM_Eventos_Partida_procurar()
{
  BM_Render_adicionar_funcao(BM_Render_esperando_oponente, NULL);
  BM_Communication_Send_match_request(BM_Player_getId());
}
