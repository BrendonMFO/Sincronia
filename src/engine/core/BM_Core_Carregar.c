#include "BM_Socket.h"
#include "BM_Core_Renders.h"
#include "BM_Core_Carregar.h"
#include "BM_Socket_events.h"
#include "BM_Recursos_Animacao.h"

int BM_Core_carregar_recursos();
int BM_Core_carregar_campo();

int BM_Core_carregar()
{
  BM_Socket_connect();
  BM_Socket_events_init();
  return BM_Core_carregar_recursos() &&
         BM_Core_carregar_campo() &&
         BM_Player_iniciar(11) &&
         BM_Oponente_iniciar(18);
}

int BM_Core_carregar_recursos()
{
  return bm_al_init() &&
         BM_Recursos_carregar_recursos() &&
         bm_events_init_queue() &&
         bm_al_mouse_callback_queue_init() &&
         BM_Animacao_iniciar_fila() &&
         BM_Render_iniciar_fila();
}

int BM_Core_carregar_campo()
{
  BM_Campo_setCampo(RESOURCE("Fases/Mapa_01.gf"));
  return BM_Campo_getCampo() == NULL ? 0 : 1;
}
