#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Rodadas.h"
#include "BM_Hexagono.h"
#include "BM_Oponente.h"
#include "BM_Core_Eventos.h"
#include "bm_allegro_main_events.h"
#include "BM_Communication_Send.h"
#include "bm_allegro_mouse_callback_queue.h"

void BM_Eventos_Jogador_Escolha_retornar();
void BM_Eventos_Jogador_Escolha_mouse(int, int);
void BM_Evento_Jogador_Escolha(ALLEGRO_EVENT, void *);

void BM_Evento_Jogador_Escolha_registrar()
{
  bm_events_add_callback(BM_Evento_Jogador_Escolha, NULL);
}

void BM_Evento_Jogador_Escolha(ALLEGRO_EVENT event, void *_parameter)
{
  switch (event.type)
  {
  case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
    return BM_Eventos_Jogador_Escolha_mouse(event.mouse.x, event.mouse.y);

  case ALLEGRO_EVENT_KEY_DOWN:
    switch (event.keyboard.keycode)
    {
    case ALLEGRO_KEY_ESCAPE:
      return BM_Eventos_Jogador_Escolha_retornar();
    }
  }
}

void BM_Eventos_Jogador_Escolha_mouse(int x, int y)
{
  BM_Campo *campo = BM_Campo_getCampo();
  BM_ALLEGRO_MOUSE_CALLBACK *mouse = bm_al_mouse_callback_queue_process(x, y);

  if (mouse == NULL)
  {
    return;
  }

  int elemento = *(int *)mouse->optional;

  if (BM_Player_disponibilidade_elemento(elemento) != 1)
  {
    return;
  }

  if (campo->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado == NEUTRO)
  {
    BM_Player_getJogador()->quantidadeTerritorio++;
  }

  BM_Player_checar_elemento(elemento);
  BM_Elemento_remover_mouse_listener();
  bm_events_remove_callback(BM_Evento_Jogador_Escolha);

  campo->hexagonos[BM_Player_getJogador()->hexagonoAtual].elemento = elemento;
  campo->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado = JOGADOR;

  BM_Render_remover_funcao(BM_Render_elementos);

  BM_Communication_Send_capture_hexagon(BM_Player_getJogador()->hexagonoAtual, elemento);

  BM_Rodada_avancar();
}

void BM_Eventos_Jogador_Escolha_retornar()
{
  BM_Elemento_remover_mouse_listener();

  bm_events_remove_callback(BM_Evento_Jogador_Escolha);

  BM_Evento_Jogador_registrar();

  BM_Render_remover_funcao(BM_Render_elementos);
}