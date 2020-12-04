#include <stdio.h>
#include <stdlib.h>
#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Recursos.h"
#include "bm_display.h"
#include "bm_allegro_main_events.h"
#include "bm_allegro_events_callback.h"

static BM_PLAYER *jogador = NULL;
static long long jogador_id = 0;

void BM_Player_elementos();

int bm_player_init(int _hexagonoInicialJogador)
{
  jogador = (BM_PLAYER *)malloc(1 * sizeof(BM_PLAYER));
  if (jogador == NULL)
  {
    fprintf(stderr, "Erro: Nao foi possivel alocar memoria para um player");
    exit(-1);
  }
  BM_Player_iniciar_valores(_hexagonoInicialJogador);

  return 1;
}

BM_PLAYER *BM_Player_getJogador()
{
  return jogador;
}

long long BM_Player_getId()
{
  return jogador_id;
}

void BM_Player_setId(long long id)
{
  jogador_id = id;
}

void BM_Player_iniciar_valores(int _hexagono)
{
  jogador->hexagonoAtual = _hexagono;
  jogador->quantidadeTerritorio = 5;
  jogador->elementosDisponivel.luz = 1;
  jogador->elementosDisponivel.trevas = 1;
  jogador->elementosDisponivel.fogo = 1;
  jogador->elementosDisponivel.agua = 1;
  jogador->elementosDisponivel.terra = 1;
  jogador->elementosDisponivel.ar = 1;
  jogador->elementosTempo.luz = 0;
  jogador->elementosTempo.trevas = 0;
  jogador->elementosTempo.fogo = 0;
  jogador->elementosTempo.agua = 0;
  jogador->elementosTempo.terra = 0;
  jogador->elementosTempo.ar = 0;
  bm_field_get()->hexagonos[_hexagono].estado = JOGADOR;
}

int BM_Player_disponibilidade_elemento(int _elemento)
{
  int *elemento = &jogador->elementosDisponivel.luz;
  return elemento[_elemento - 1];
}

void BM_Player_checar_elemento(int _elemento)
{
  int *elemento = &jogador->elementosDisponivel.luz;
  elemento[_elemento - 1] = 0;
  BM_Player_elementos();
}

void BM_Player_elementos()
{
  int i, *elemento, vazio = 1;
  elemento = &jogador->elementosDisponivel.luz;
  for (i = 0; i < 6; i++, elemento++)
  {
    if (*elemento == 1)
      vazio = 0;
  }
  if (vazio == 1)
  {
    elemento = &jogador->elementosDisponivel.luz;
    for (i = 0; i < 6; i++, elemento++)
    {
      *elemento = 1;
    }
  }
}

void BM_Player_checar_tempo()
{
  int *elementoTempo, *elemento, i;
  elementoTempo = &jogador->elementosTempo.luz;
  for (i = 0; i < 6; i++, elementoTempo++)
  {
    (*elementoTempo)++;
  }
  elementoTempo = &jogador->elementosTempo.luz;
  elemento = &jogador->elementosDisponivel.luz;
  for (i = 0; i < 6; i++, elementoTempo++, elemento++)
  {
    if (*elementoTempo == 4)
    {
      *elementoTempo = 0;
      *elemento = 1;
    }
  }
}

BM_HEXAGONO *BM_Player_mover(BM_PLAYER *_player, int _mouseX, int _mouseY)
{
  BM_Campo *campo = bm_field_get();
  BM_HEXAGONO *hexagono = NULL, *aux = NULL;
  int i, j, pos, width, height;
  for (i = 0; i < campo->quantidade; i++)
  {
    hexagono = &campo->hexagonos[i];
    width = BM_FIX_XW(hexagono->posicaoX) + SPRITES(BM_IMG_HEXAGONO)->ajusteW;
    height = BM_FIX_YH(hexagono->posicaoY) + SPRITES(BM_IMG_HEXAGONO)->ajusteH;
    if (_mouseX >= BM_FIX_XW(hexagono->posicaoX) && _mouseX <= width &&
        _mouseY >= BM_FIX_YH(hexagono->posicaoY) && _mouseY <= height)
    {
      break;
    }
  }
  if (i >= campo->quantidade || i == _player->hexagonoAtual || hexagono->estado == ADVERSARIO)
  {
    return NULL;
  }
  if (hexagono->estado == JOGADOR)
  {
    _player->hexagonoAtual = hexagono->id;
    return hexagono;
  }
  else
  {
    for (j = 0; j < 6; j++)
    {
      pos = hexagono->conexoes[j];
      if (pos != -1)
      {
        aux = &campo->hexagonos[pos];
        if (aux->estado == JOGADOR)
        {
          _player->hexagonoAtual = hexagono->id;
          return hexagono;
        }
      }
    }
  }
  return NULL;
}
