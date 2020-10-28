#include "BM_Core_Renders.h"
#include "BM_Recursos_Animacao.h"

void BM_Render_Animacao_render(BM_ANIMACAO *aux);
void BM_Render_Animacao_checar(BM_ANIMACAO *aux);

void BM_Render_animacao()
{
  BM_ANIMACAO *aux;

  for (aux = BM_Animacao_obter_fila()->first; aux != NULL; aux = aux->next)
  {
    BM_Render_Animacao_render(aux);
  }

  for (aux = BM_Animacao_obter_fila()->first; aux != NULL; aux = aux->next)
  {
    BM_Render_Animacao_checar(aux);
  }
}

void BM_Render_Animacao_render(BM_ANIMACAO *aux)
{
  int sourceX = aux->sprite->imagem->width * aux->frameAtualColuna;
  int sourceY = aux->sprite->imagem->height * aux->frameAtualLinha;
  BM_Render_regiao_escalonada(aux->sprite, sourceX, sourceY, aux->destinoX, aux->destinoY, aux->destinoW, aux->destinoH, 0);
  if (aux->render == 1)
  {
    aux->render = 2;
    BM_Animacao_avancar(aux);
  }
}

void BM_Render_Animacao_checar(BM_ANIMACAO *aux)
{
  if (aux->finalizado != 1)
  {
    aux = aux->next;
    return;
  }

  if (aux->next != NULL)
  {
    aux = aux->next;
    BM_Animacao_remover(aux->previous);
    return;
  }

  BM_Animacao_remover(aux);
}