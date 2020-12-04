#ifndef _BM_MAIN_RENDERS_
#define _BM_MAIN_RENDERS_

#include "bm_allegro.h"
#include "BM_Recursos_Conteudo.h"

typedef void (*BM_RENDER_CALLBACK)(void *);

typedef struct BM_RENDER_S
{
  int active;
  BM_RENDER_CALLBACK callback;
  void *parameter;
  struct BM_RENDER_S *previous;
  struct BM_RENDER_S *next;
} BM_RENDER;

typedef struct BM_RENDER_FILA_S
{
  BM_RENDER *first;
  BM_RENDER *last;
} BM_RENDER_QUEUE;

int bm_render_init_queue();

void bm_render_add_callback(BM_RENDER_CALLBACK _callback, void *_parameter);

void bm_render_remove_callback(BM_RENDER_CALLBACK _callback);

void bm_render_normal(BM_SPRITES *_sprite, int _xPosition, int _y, int _flag);

void bm_render_region(BM_SPRITES *_sprite, int _sX, int _sY, int _dX, int _dY, int _flag);

void bm_render_region_scaled(BM_SPRITES *_sprite, int _sX, int _sY, int _dX, int _dY, int _dW, int _dH, int _flag);

void BM_Render_loop();

void BM_Render_inicial();

#endif