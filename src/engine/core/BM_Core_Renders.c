#include <string.h>
#include "BM_Utils.h"
#include "BM_Recursos.h"
#include "BM_Core_Renders.h"
#include "bm_display.h"
#include "BM_Recursos_Conteudo.h"

static BM_RENDER_FILA *renderFila = NULL;

void BM_Render_renderizar_fila();
BM_RENDER *BM_Render_procurar_fila(BM_RENDER_FUNCAO _callback);
void BM_Render_normal(BM_SPRITES *_sprite, int _xPosition, int _y, int _flag);
void BM_Render_regiao(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _flag);
void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag);

void BM_Render_normal(BM_SPRITES *_sprite, int _xPosition, int _y, int _flag)
{
  al_draw_scaled_bitmap(
      _sprite->Imagem,
      0, 0, _sprite->imagem->width, _sprite->imagem->height,
      BM_FIX_XW(_xPosition), BM_FIX_YH(_y), _sprite->ajusteW, _sprite->ajusteH, _flag);
}

void BM_Render_regiao(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _flag)
{
  al_draw_scaled_bitmap(
      _sprite->Imagem,
      _sX, _sY,
      _sprite->imagem->width, _sprite->imagem->height,
      BM_FIX_XW(_dX), BM_FIX_YH(_dY),
      _sprite->ajusteW, _sprite->ajusteH, _flag);
}

void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag)
{
  al_draw_scaled_bitmap(
      _sprite->Imagem,
      _sX, _sY, _sprite->imagem->width, _sprite->imagem->height,
      BM_FIX_XW(_dX), BM_FIX_YH(_dY),
      BM_FIX_XW(_dW), BM_FIX_YH(_sprite->ajusteH), _flag);
}

void BM_Render_loop()
{
  BM_Render_renderizar_fila();
  al_flip_display();
}

int BM_Render_iniciar_fila()
{
  renderFila = (BM_RENDER_FILA *)malloc(1 * sizeof(BM_RENDER_FILA));
  if (renderFila == NULL)
  {
    printf("Erro: Nao foi possivel alocar memoria para a fila de renderizacao\n");
    return 0;
  }
  renderFila->first = NULL;
  renderFila->last = NULL;
  return 1;
}

void BM_Render_adicionar_funcao(BM_RENDER_FUNCAO _callback, void *_parameter)
{
  BM_RENDER *aux = (BM_RENDER *)malloc(1 * sizeof(BM_RENDER));

  BM_Utils_ponteiro(aux, "Erro: Nao foi possivel alocar memoria para uma callback de renderizacao");

  aux->active = 1;
  aux->next = NULL;
  aux->callback = _callback;
  aux->parameter = _parameter;

  if (renderFila->first == NULL)
  {
    renderFila->first = aux;
    renderFila->last = aux;
    aux->previous = NULL;
  }
  else
  {
    renderFila->last->next = aux;
    aux->previous = renderFila->last;
    renderFila->last = aux;
  }
}

void BM_Render_remover_funcao(BM_RENDER_FUNCAO _callback)
{
  BM_RENDER *aux = BM_Render_procurar_fila(_callback);
  BM_Utils_ponteiro(aux, "Ponteiro da callback de renderizacao nao encontrado.");

  aux->active = 0;

  if (renderFila->first == renderFila->last)
  {
    renderFila->first = NULL;
    renderFila->last = NULL;
  }
  else
  {
    if (aux->previous != NULL)
    {
      aux->previous->next = aux->next;
    }
    else
    {
      renderFila->first = aux->next;
    }

    if (aux->next != NULL)
    {
      aux->next->previous = aux->previous;
    }
    else
    {
      renderFila->last = aux->previous;
    }
  }
}

void BM_Render_renderizar_fila()
{
  BM_RENDER *aux;
  for (aux = renderFila->first; aux != NULL; aux = aux->next)
  {
    aux->callback(aux->parameter);
  }
}

BM_RENDER *BM_Render_procurar_fila(BM_RENDER_FUNCAO _callback)
{
  BM_RENDER *aux;
  for (aux = renderFila->first; aux != NULL; aux = aux->next)
  {
    if (aux->callback == _callback)
    {
      break;
    }
  }
  return aux;
}