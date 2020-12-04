#include "BM_Campo.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Hexagono.h"
#include "BM_Tutorial.h"
#include "bm_core_events.h"
#include "bm_allegro_main_events.h"

void BM_Eventos_Tutorial_avancar();
void BM_Eventos_Tutorial_iniciar_jogo();
void BM_Eventos_Tutorial(ALLEGRO_EVENT, void *);

void BM_Eventos_Tutorial_registrar()
{
  bm_events_add_callback(BM_Eventos_Tutorial, NULL);
}

void BM_Eventos_Tutorial(ALLEGRO_EVENT event, void *_parameter)
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

void BM_Eventos_Tutorial_iniciar_jogo()
{
  bm_render_remove_callback(BM_Render_tutorial);
  bm_events_remove_callback(BM_Eventos_Tutorial);
  BM_Eventos_Partida_procurar();
}

void BM_Eventos_Tutorial_avancar()
{
  if (BM_Render_obter_tutorial() == 9)
  {
    BM_Eventos_Tutorial_iniciar_jogo();
  }
  else
  {
    BM_Render_avancar_tutorial();
  }
}