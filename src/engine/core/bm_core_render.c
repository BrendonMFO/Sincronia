#include <string.h>
#include "bm_utils.h"
#include "bm_display.h"
#include "BM_Recursos.h"
#include "bm_core_render.h"
#include "BM_Recursos_Conteudo.h"

static BM_RENDER_QUEUE *render_queue = NULL;

void bm_render_queue_execute();
BM_RENDER *bm_render_queue_search(BM_RENDER_CALLBACK _callback);
void bm_render_normal(BM_SPRITES *_sprite, int _xPosition, int _y, int _flag);
void bm_render_region(BM_SPRITES *_sprite, int _sX, int _sY, int _dX, int _dY, int _flag);
void bm_render_region_scaled(BM_SPRITES *_sprite, int _sX, int _sY, int _dX, int _dY, int _dW, int _dH, int _flag);

void bm_render_normal(BM_SPRITES *_sprite, int _xPosition, int _y, int _flag)
{
  al_draw_scaled_bitmap(
      _sprite->image->bitmap,
      0, 0, _sprite->image->width, _sprite->image->height,
      BM_FIX_XW(_xPosition), BM_FIX_YH(_y), _sprite->ajusteW, _sprite->ajusteH, _flag);
}

void bm_render_region(BM_SPRITES *_sprite, int _sX, int _sY, int _dX, int _dY, int _flag)
{
  al_draw_scaled_bitmap(
      _sprite->image->bitmap,
      _sX, _sY,
      _sprite->image->width, _sprite->image->height,
      BM_FIX_XW(_dX), BM_FIX_YH(_dY),
      _sprite->ajusteW, _sprite->ajusteH, _flag);
}

void bm_render_region_scaled(BM_SPRITES *_sprite, int _sX, int _sY, int _dX, int _dY, int _dW, int _dH, int _flag)
{
  al_draw_scaled_bitmap(
      _sprite->image->bitmap,
      _sX, _sY, _sprite->image->width, _sprite->image->height,
      BM_FIX_XW(_dX), BM_FIX_YH(_dY),
      BM_FIX_XW(_dW), BM_FIX_YH(_sprite->ajusteH), _flag);
}

void BM_Render_loop()
{
  bm_render_queue_execute();
  al_flip_display();
}

int bm_render_init_queue()
{
  render_queue = (BM_RENDER_QUEUE *)malloc(1 * sizeof(BM_RENDER_QUEUE));
  bm_utils_pointer(render_queue, "Error: Could not allocate memory render_queue");
  render_queue->first = NULL;
  render_queue->last = NULL;
  return 1;
}

void bm_render_add_callback(BM_RENDER_CALLBACK _callback, void *_parameter)
{
  BM_RENDER *aux = (BM_RENDER *)malloc(1 * sizeof(BM_RENDER));
  bm_utils_pointer(aux, "Error: Could not allocate memory aux");

  aux->active = 1;
  aux->next = NULL;
  aux->callback = _callback;
  aux->parameter = _parameter;

  if (render_queue->first == NULL)
  {
    render_queue->first = aux;
    render_queue->last = aux;
    aux->previous = NULL;
  }
  else
  {
    render_queue->last->next = aux;
    aux->previous = render_queue->last;
    render_queue->last = aux;
  }
}

void bm_render_remove_callback(BM_RENDER_CALLBACK _callback)
{
  BM_RENDER *aux = bm_render_queue_search(_callback);
  bm_utils_pointer(aux, "Error: Could not allocate memory aux");

  aux->active = 0;

  if (render_queue->first == render_queue->last)
  {
    render_queue->first = NULL;
    render_queue->last = NULL;
  }
  else
  {
    if (aux->previous != NULL)
    {
      aux->previous->next = aux->next;
    }
    else
    {
      render_queue->first = aux->next;
    }

    if (aux->next != NULL)
    {
      aux->next->previous = aux->previous;
    }
    else
    {
      render_queue->last = aux->previous;
    }
  }
}

void bm_render_queue_execute()
{
  BM_RENDER *aux;
  for (aux = render_queue->first; aux != NULL; aux = aux->next)
  {
    aux->callback(aux->parameter);
  }
}

BM_RENDER *bm_render_queue_search(BM_RENDER_CALLBACK _callback)
{
  BM_RENDER *aux;
  for (aux = render_queue->first; aux != NULL; aux = aux->next)
  {
    if (aux->callback == _callback)
    {
      break;
    }
  }
  return aux;
}