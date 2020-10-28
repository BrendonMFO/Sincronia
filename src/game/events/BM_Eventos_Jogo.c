#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Rodadas.h"
#include "BM_Oponente.h"
#include "BM_Core_Eventos.h"
#include "bm_allegro_main_events.h"

void BM_Eventos_Jogo_reiniciar();
void BM_Eventos_Jogo_Executando();
void BM_Eventos_Jogo_verificar_fim(ALLEGRO_EVENT, void *_parameter);

static int executando = 0;

void BM_Eventos_Jogo_registrar()
{
  BM_Eventos_Jogo_Executando();
  bm_events_add_callback(BM_Eventos_Jogo_verificar_fim, NULL);
  BM_Render_adicionar_funcao(BM_Render_rodada, NULL);
}

void BM_Eventos_Jogo_eventos(ALLEGRO_EVENT event, void *_parameter)
{
  switch (event.type)
  {
  case ALLEGRO_EVENT_KEY_DOWN:
    switch (event.keyboard.keycode)
    {
    case ALLEGRO_KEY_R:
      return BM_Eventos_Jogo_reiniciar();
    }
  }
}

void BM_Eventos_Jogo_verificar_fim(ALLEGRO_EVENT event, void *_parameter)
{
  if (BM_Rodada_get_restantes() == 0 ||
      BM_Player_getJogador()->quantidadeTerritorio == 0 ||
      BM_Player_getOpponentPlayer()->quantidadeTerritorio == 0)
  {
    BM_Render_adicionar_funcao(BM_Render_resultado, NULL);
    bm_events_add_callback(BM_Eventos_Jogo_eventos, NULL);
    bm_events_remove_callback(BM_Eventos_Jogo_verificar_fim);
    executando = 0;
  }
}

void BM_Eventos_Jogo_Executando()
{
  if (executando == 0)
  {
    BM_Rodada_set(50);
    executando = 1;
  }
}

void BM_Eventos_Jogo_reiniciar()
{
  BM_Campo_redefinir();
  BM_Oponente_iniciar_valores(BM_Campo_getCampo()->quantidade - 1);
  bm_events_remove_callback(BM_Eventos_Jogo_eventos);
  BM_Render_remover_funcao(BM_Render_resultado);
  BM_Eventos_Jogo_registrar();
}