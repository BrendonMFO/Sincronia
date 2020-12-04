#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Oponente.h"
#include "bm_core_render.h"
#include "BM_Communication.h"
#include "bm_socket_events.h"
#include "bm_socket_structs.h"
#include "BM_Communication_Send.h"
#include "BM_Communication_Receive.h"

void BM_Eventos_Partida_procurar()
{
  bm_render_add_callback(BM_Render_esperando_oponente, NULL);
  BM_Communication_Send_match_request(BM_Player_getId());
}
