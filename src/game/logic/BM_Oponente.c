#include <stdio.h>
#include <stdarg.h>
#include "BM_Campo.h"
#include "BM_Rodadas.h"
#include "BM_Eventos.h"
#include "BM_Hexagono.h"
#include "BM_Oponente.h"
#include "bm_core_events.h"
#include "bm_allegro_main_events.h"

static BM_PLAYER *ia = NULL;
static int BM_Oponente_socket;

int BM_Oponente_checar_elemento();

int bm_oponent_init(int _hexagonoAtual)
{
  ia = (BM_PLAYER *)malloc(sizeof(BM_PLAYER));

  if (ia == NULL)
  {
    fprintf(stderr, "Erro: Nao foi possivel alocar memoria para um player");
    exit(-1);
  }

  BM_Oponente_iniciar_valores(_hexagonoAtual);

  return 1;
}

BM_PLAYER *BM_Player_getOpponentPlayer()
{
  return ia;
}

void BM_Oponente_set_socket(int socket)
{
  BM_Oponente_socket = socket;
}

void BM_Oponente_capture_hexagon(int hexagon, int element)
{
  if (bm_field_get()->hexagonos[ia->hexagonoAtual].estado != ADVERSARIO)
  {
    ia->quantidadeTerritorio++;
  }

  BM_Hexagono_alterar(hexagon, ADVERSARIO, element);
}

int BM_Oponente_get_socket()
{
  return BM_Oponente_socket;
}

void BM_Oponente_set_hexagon(int hexagon)
{
  ia->hexagonoAtual = hexagon;
}

void BM_Oponente_iniciar_valores(int _hexagono)
{
  ia->quantidadeTerritorio = 5;
  ia->elementosDisponivel.luz = 1;
  ia->elementosDisponivel.trevas = 1;
  ia->elementosDisponivel.fogo = 1;
  ia->elementosDisponivel.agua = 1;
  ia->elementosDisponivel.terra = 1;
  ia->elementosDisponivel.ar = 1;
  ia->elementosTempo.luz = 0;
  ia->elementosTempo.trevas = 0;
  ia->elementosTempo.fogo = 0;
  ia->elementosTempo.agua = 0;
  ia->elementosTempo.terra = 0;
  ia->elementosTempo.ar = 0;
  BM_Oponente_set_hexagon(_hexagono);
  bm_field_get()->hexagonos[_hexagono].estado = ADVERSARIO;
}

int BM_Oponente_checar_elemento()
{
  int elementosDisponiveis = 0, ordemElementos[6], vazio = 1, *elemento, i, resultado;
  elemento = &ia->elementosDisponivel.luz;
  for (i = 0; i < 6; i++, elemento++)
  {
    if (*elemento == 1)
    {
      ordemElementos[elementosDisponiveis++] = i + 1;
      vazio = 0;
    }
  }
  if (vazio == 1)
  {
    elemento = &ia->elementosDisponivel.luz;
    for (i = 0; i < 6; i++, elemento++)
    {
      *elemento = 1;
    }
  }
  resultado = ordemElementos[rand() % elementosDisponiveis];
  elemento = &ia->elementosDisponivel.luz;
  elemento[resultado] = 0;
  return ordemElementos[rand() % elementosDisponiveis];
}

void BM_Oponente_checar_tempo()
{
  int *elementoTempo, *elemento, i;
  elementoTempo = &ia->elementosTempo.luz;
  for (i = 0; i < 6; i++, elementoTempo++)
  {
    (*elementoTempo)++;
  }
  elementoTempo = &ia->elementosTempo.luz;
  elemento = &ia->elementosDisponivel.luz;
  for (i = 0; i < 6; i++, elementoTempo++, elemento++)
  {
    if (*elementoTempo == 4)
    {
      *elementoTempo = 0;
      *elemento = 1;
    }
  }
}

void BM_Oponente_executar_ataque(int _alvo)
{
  BM_Campo *campo = bm_field_get();
  switch (BM_Hexagono_batalha(campo->hexagonos[_alvo].id, ia->hexagonoAtual, ADVERSARIO, JOGADOR))
  {
  case VITORIA_ATAQUE:
    campo->hexagonos[_alvo].estado = ADVERSARIO;
    BM_Player_getOpponentPlayer()->quantidadeTerritorio++;
    BM_Player_getJogador()->quantidadeTerritorio--;
    break;
  case VITORIA_DEFESA:
    campo->hexagonos[ia->hexagonoAtual].estado = JOGADOR;
    BM_Player_getOpponentPlayer()->quantidadeTerritorio--;
    BM_Player_getJogador()->quantidadeTerritorio++;
    break;
  }
  campo->hexagonos[_alvo].alvo = HEXAGONO_NORMAL;
  BM_Hexagono_desmarcar_sincronia(ADVERSARIO);
  BM_Rodada_avancar();
}