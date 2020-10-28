#ifndef _BM_ALLEGRO_CALLBACKS_
#define _BM_ALLEGRO_CALLBACKS_

#include "bm_allegro_main_events.h"

typedef void (*BM_EVENT_CALLBACK_TYPE)(ALLEGRO_EVENT, void *);

typedef struct BM_EVENT_CALLBACK_S
{
  struct BM_EVENT_CALLBACK_S *previous;
  int active;
  void *parameter;
  BM_EVENT_CALLBACK_TYPE callback;
  struct BM_EVENT_CALLBACK_S *next;
} BM_EVENT_CALLBACK;

typedef struct BM_EVENTS_QUEUE_S
{
  BM_EVENT_CALLBACK *first;
  BM_EVENT_CALLBACK *last;
} BM_EVENTS_QUEUE;

int bm_events_init_queue();

int bm_events_add_callback(BM_EVENT_CALLBACK_TYPE _callback, void *_parameter);

void bm_events_remove_callback(BM_EVENT_CALLBACK_TYPE _callback);

BM_EVENTS_QUEUE *bm_events_get_callback_queue();

#endif