#ifndef _MOUSE_CALLBACK_QUEUE_
#define _MOUSE_CALLBACK_QUEUE_

#include "bm_allegro.h"

typedef void (*BM_ALLEGRO_MOUSE_CALLBACK_TYPE)(int, ...);

typedef struct BM_ALLEGRO_MOUSE_CALLBACK_S
{
  int initialX;
  int initialY;
  int finalX;
  int finalY;
  BM_ALLEGRO_MOUSE_CALLBACK_TYPE callback;
  void *optional;
  struct BM_ALLEGRO_MOUSE_CALLBACK_S *previous;
  struct BM_ALLEGRO_MOUSE_CALLBACK_S *next;
} BM_ALLEGRO_MOUSE_CALLBACK;

typedef struct BM_EVENTO_MOUSE_FILA_S
{
  BM_ALLEGRO_MOUSE_CALLBACK *first;
  BM_ALLEGRO_MOUSE_CALLBACK *last;
} MOUSE_CALLBACK_QUEUE;

int bm_al_mouse_callback_queue_init();

int bm_al_mouse_callback_queue_add(BM_ALLEGRO_MOUSE_CALLBACK_TYPE _callback, int _iX, int _iY, int _fX, int _fY, void *_opcional);

void bm_al_mouse_callback_queue_remove(int _xPosition, int _yPosition, int _xFinal, int _yFinal);

MOUSE_CALLBACK_QUEUE *bm_al_mouse_get_callback_queue();

BM_ALLEGRO_MOUSE_CALLBACK *bm_al_mouse_callback_queue_process(int _clickX, int _clickY);

#endif