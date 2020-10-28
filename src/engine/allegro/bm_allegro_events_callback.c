#include "bm_allegro.h"
#include "bm_allegro_events_callback.h"

static BM_EVENTS_QUEUE *bm_events_queue = NULL;

BM_EVENT_CALLBACK *bm_events_queue_search(BM_EVENT_CALLBACK_TYPE _callback);

int bm_events_init_queue()
{
  bm_events_queue = (BM_EVENTS_QUEUE *)malloc(sizeof(BM_EVENTS_QUEUE));

  if (bm_events_queue == NULL)
  {
    exit(-1);
  }

  bm_events_queue->first = NULL;
  bm_events_queue->last = NULL;

  return 1;
}

int bm_events_add_callback(BM_EVENT_CALLBACK_TYPE _callback, void *_parameter)
{
  BM_EVENT_CALLBACK *aux = (BM_EVENT_CALLBACK *)malloc(sizeof(BM_EVENT_CALLBACK));

  if (aux == NULL)
  {
    exit(-1);
  }

  aux->active = 1;
  aux->callback = _callback;
  aux->parameter = _parameter;
  aux->next = NULL;

  if (bm_events_queue->last == NULL)
  {
    bm_events_queue->first = aux;
    bm_events_queue->last = aux;
    aux->previous = NULL;
  }
  else
  {
    bm_events_queue->last->next = aux;
    aux->previous = bm_events_queue->last;
    bm_events_queue->last = aux;
  }
  
  return 1;
}

void bm_events_remove_callback(BM_EVENT_CALLBACK_TYPE _callback)
{
  BM_EVENT_CALLBACK *aux = bm_events_queue_search(_callback);

  if (aux == NULL)
  {
    return;
  }

  aux->active = 0;

  if (bm_events_queue->first == bm_events_queue->last)
  {
    bm_events_queue->first = NULL;
    bm_events_queue->last = NULL;
  }
  else
  {
    if (aux->previous != NULL)
    {
      aux->previous->next = aux->next;
    }
    else
    {
      bm_events_queue->first = aux->next;
    }

    if (aux->next != NULL)
    {
      aux->next->previous = aux->previous;
    }
    else
    {
      bm_events_queue->last = aux->previous;
    }
  }
}

BM_EVENT_CALLBACK *bm_events_queue_search(BM_EVENT_CALLBACK_TYPE _callback)
{
  BM_EVENT_CALLBACK *aux;

  for (aux = bm_events_queue->first; aux != NULL; aux = aux->next)
  {
    if (aux->callback == _callback)
    {
      return aux;
    }
  }

  return NULL;
}

BM_EVENTS_QUEUE *bm_events_get_callback_queue()
{
  return bm_events_queue;
}