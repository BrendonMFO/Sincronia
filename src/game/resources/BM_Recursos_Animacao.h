#ifndef _BM_RESOURCES_ANIMACAO_
#define _BM_RESOURCES_ANIMACAO_

#include "BM_Recursos_Conteudo.h"

typedef struct BM_ANIMACAO_S
{
  BM_SPRITES *sprite;
  int frameAtualLinha;
  int frameAtualColuna;
  int render;
  int destinoW;
  int destinoH;
  int destinoX;
  int destinoY;
  int tempoAtualizacao;
  int tempoAtual;
  int finalizado;
  struct BM_ANIMACAO_S *previous;
  struct BM_ANIMACAO_S *next;
} BM_ANIMACAO;

typedef struct BM_ANIMACAO_FILA_S
{
  BM_ANIMACAO *first;
  BM_ANIMACAO *last;
} BM_ANIMACAO_FILA;

BM_ANIMACAO_FILA *BM_Animacao_obter_fila();

int bm_animation_init_queue();

int BM_Animacao_adicionar(BM_SPRITES *_sprite, int _renderW, int _renderH, int _renderX, int _renderY, double _tempo);

void BM_Animacao_remover(BM_ANIMACAO *_animacao);

void BM_Animacao_avancar(BM_ANIMACAO *_animacao);

#endif