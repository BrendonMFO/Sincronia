#ifndef _BM_MAIN_RENDERS_
#define _BM_MAIN_RENDERS_

#include "bm_allegro.h"
#include "BM_Recursos_Conteudo.h"

#define RENDER_DADOS_REGIAO int _sX, int _sY, int _dX, int _dY

typedef void (*BM_RENDER_FUNCAO)(void *);

typedef struct BM_RENDER_S
{
  int active;
  BM_RENDER_FUNCAO callback;
  void *parameter;
  struct BM_RENDER_S *previous;
  struct BM_RENDER_S *next;
} BM_RENDER;

typedef struct BM_RENDER_FILA_S
{
  BM_RENDER *first;
  BM_RENDER *last;
} BM_RENDER_FILA;

int BM_Render_iniciar_fila();

void BM_Render_adicionar_funcao(BM_RENDER_FUNCAO _callback, void *_parameter);

void BM_Render_remover_funcao(BM_RENDER_FUNCAO _callback);

void BM_Render_normal(BM_SPRITES *_sprite, int _xPosition, int _y, int _flag);

void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag);

void BM_Render_regiao(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _flag);

void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag);

void BM_Render_loop();

void BM_Render_inicial();

#endif