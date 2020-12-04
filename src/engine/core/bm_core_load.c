#include "bm_socket.h"
#include "bm_core_load.h"
#include "bm_core_render.h"
#include "bm_socket_events.h"
#include "BM_Recursos_Animacao.h"

int bm_core_load_field();
int bm_core_load_resources();

int bm_core_load()
{
  bm_socket_connect();
  bm_socket_events_init();
  return bm_core_load_resources() &&
         bm_core_load_field() &&
         bm_player_init(11) &&
         bm_oponent_init(18);
}

int bm_core_load_resources()
{
  return bm_al_init() &&
         bm_resource_load() &&
         bm_events_init_queue() &&
         bm_al_mouse_callback_queue_init() &&
         bm_animation_init_queue() &&
         bm_render_init_queue();
}

int bm_core_load_field()
{
  bm_field_set(RESOURCE("Fases/Mapa_01.gf"));
  return bm_field_get() == NULL ? 0 : 1;
}
