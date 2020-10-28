#include <string.h>
#include "bm_display.h"
#include "bm_allegro_mouse_callback_queue.h"

static MOUSE_CALLBACK_QUEUE *mouse_queue = NULL;

BM_ALLEGRO_MOUSE_CALLBACK *bm_al_mouse_queue_search(int _xPosition, int _yPosition, int _xFinal, int _yFinal);

int bm_al_mouse_callback_queue_init()
{
  mouse_queue = (MOUSE_CALLBACK_QUEUE *)malloc(1 * sizeof(MOUSE_CALLBACK_QUEUE));

  if (mouse_queue == NULL)
  {
    exit(-1);
  }

  mouse_queue->first = NULL;
  mouse_queue->last = NULL;

  return 1;
}

int bm_al_mouse_callback_queue_add(BM_ALLEGRO_MOUSE_CALLBACK_TYPE _callback, int _iX, int _iY, int _fX, int _fY, void *_opcional)
{
  BM_ALLEGRO_MOUSE_CALLBACK *aux = (BM_ALLEGRO_MOUSE_CALLBACK *)malloc(sizeof(BM_ALLEGRO_MOUSE_CALLBACK));

  if (aux == NULL)
  {
    exit(-1);
  }

  aux->initialX = BM_FIX_XW(_iX);
  aux->initialY = BM_FIX_YH(_iY);
  aux->finalX = BM_FIX_XW(_fX);
  aux->finalY = BM_FIX_YH(_fY);
  aux->callback = _callback;
  aux->optional = _opcional;
  aux->previous = NULL;

  if (mouse_queue->first == NULL)
  {
    mouse_queue->first = aux;
    mouse_queue->last = aux;
    aux->next = NULL;
  }
  else
  {
    mouse_queue->first->previous = aux;
    aux->next = mouse_queue->first;
    mouse_queue->first = aux;
  }

  return 1;
}

void bm_al_mouse_callback_queue_remove(int _xPosition, int _yPosition, int _xFinal, int _yFinal)
{
  BM_ALLEGRO_MOUSE_CALLBACK *aux = bm_al_mouse_queue_search(_xPosition, _yPosition, _xFinal, _yFinal);

  if (aux == NULL)
  {
    return;
  }

  if (mouse_queue->first == mouse_queue->last)
  {
    mouse_queue->first = NULL;
    mouse_queue->last = NULL;
  }
  else
  {
    if (aux->previous != NULL)
    {
      aux->previous->next = aux->next;
    }
    else
    {
      mouse_queue->first = aux->next;
    }

    if (aux->next != NULL)
    {
      aux->next->previous = aux->previous;
    }
    else
    {
      mouse_queue->last = aux->previous;
    }
  }

  free(aux->optional);
  free(aux);
}

MOUSE_CALLBACK_QUEUE *bm_al_mouse_get_callback_queue()
{
  return mouse_queue;
}

BM_ALLEGRO_MOUSE_CALLBACK *bm_al_mouse_callback_queue_process(int _clickX, int _clickY)
{
  BM_ALLEGRO_MOUSE_CALLBACK *aux;

  for (aux = mouse_queue->first; aux != NULL; aux = aux->next)
  {
    if (_clickX >= aux->initialX && _clickX <= aux->finalX &&
        _clickY >= aux->initialY && _clickY <= aux->finalY)
    {
      break;
    }
  }

  return aux;
}

BM_ALLEGRO_MOUSE_CALLBACK *bm_al_mouse_queue_search(int _xPosition, int _yPosition, int _xFinal, int _yFinal)
{
  BM_ALLEGRO_MOUSE_CALLBACK *aux;

  for (aux = mouse_queue->first; aux != NULL; aux = aux->next)
  {
    if (aux->initialX == _xPosition && aux->initialY == _yPosition &&
        aux->finalX == _xFinal && aux->finalY == _yFinal)
    {
      break;
    }
  }

  return aux;
}