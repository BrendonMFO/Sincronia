#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Eventos.h"
#include "BM_Hexagono.h"
#include "BM_Oponente.h"
#include "bm_core_events.h"
#include "bm_allegro_main_events.h"
#include "BM_Communication_Send.h"
#include "bm_allegro_mouse_callback_queue.h"
#include "bm_allegro_events_callback.h"

void BM_Eventos_Jogador_Alvo_voltar();
void BM_Eventos_Jogador_Alvo_empate();
void BM_Eventos_Jogador_Alvo_click(int, int);
void BM_Evento_Jogador_Alvo(ALLEGRO_EVENT, void *);
void BM_Eventos_Jogador_Alvo_vitoria_ataque(BM_HEXAGONO *);
void BM_Eventos_Jogador_Alvo_vitoria_defesa(BM_HEXAGONO *);

void BM_Evento_Jogador_alvo_registrar()
{
  bm_events_add_callback(BM_Evento_Jogador_Alvo, NULL);
}

void BM_Evento_Jogador_Alvo(ALLEGRO_EVENT event, void *_parameter)
{
  switch (event.type)
  {
  case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
    return BM_Eventos_Jogador_Alvo_click(event.mouse.x, event.mouse.y);

  case ALLEGRO_EVENT_KEY_DOWN:
    switch (event.keyboard.keycode)
    {
    case ALLEGRO_KEY_A:
      return BM_Eventos_Jogador_Alvo_voltar();
    }
  }
}

void BM_Eventos_Jogador_Alvo_voltar()
{
  BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

  BM_Hexagono_desmarcar_sincronia(JOGADOR);

  bm_events_remove_callback(BM_Evento_Jogador_Alvo);

  BM_Evento_Jogador_registrar();

  BM_Communication_Send_toggle_sincronia(0);
}

void BM_Eventos_Jogador_Alvo_click(int x, int y)
{
  BM_HEXAGONO *hexagonoClick = BM_Hexagono_click(x, y);

  if (hexagonoClick == NULL || hexagonoClick->estado != ADVERSARIO || hexagonoClick->alvo == 0)
  {
    return;
  }

  BM_Communication_Send_battle(hexagonoClick->id);

  switch (BM_Hexagono_batalha(hexagonoClick->id, BM_Player_getJogador()->hexagonoAtual, JOGADOR, ADVERSARIO))
  {
  case VITORIA_ATAQUE:
    BM_Eventos_Jogador_Alvo_vitoria_ataque(hexagonoClick);
    break;

  case VITORIA_DEFESA:
    BM_Eventos_Jogador_Alvo_vitoria_defesa(hexagonoClick);
    break;

  case EMPATE:
    BM_Eventos_Jogador_Alvo_empate();
    break;
  }

  bm_events_remove_callback(BM_Evento_Jogador_Alvo);
}

void BM_Eventos_Jogador_Alvo_empate()
{
  BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

  BM_Hexagono_desmarcar_sincronia(JOGADOR);
}

void BM_Eventos_Jogador_Alvo_vitoria_ataque(BM_HEXAGONO *hexagonoClick)
{
  BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

  BM_Hexagono_desmarcar_sincronia(JOGADOR);

  BM_Player_getJogador()->hexagonoAtual = hexagonoClick->id;

  BM_Communication_Send_move_player(hexagonoClick->id);

  BM_Player_getJogador()->quantidadeTerritorio++;

  BM_Player_getOpponentPlayer()->quantidadeTerritorio--;

  hexagonoClick->estado = JOGADOR;
}

void BM_Eventos_Jogador_Alvo_vitoria_defesa(BM_HEXAGONO *hexagonoClick)
{
  BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

  BM_Hexagono_desmarcar_sincronia(JOGADOR);

  BM_Player_getJogador()->quantidadeTerritorio--;

  BM_Player_getOpponentPlayer()->quantidadeTerritorio++;

  bm_field_get()->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado = ADVERSARIO;
}
