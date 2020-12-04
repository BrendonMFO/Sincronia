#include "bm_core_render.h"
#include "BM_Recursos_Animacao.h"

void BM_Render_Animacao_render(BM_ANIMACAO *aux);
void BM_Render_Animacao_checar(BM_ANIMACAO *aux);

void BM_Render_animacao()
{
  BM_ANIMACAO *aux = BM_Animacao_obter_fila()->first;
  while(aux != NULL) {
    BM_Render_Animacao_render(aux);
    BM_Render_Animacao_checar(aux);
    aux = aux->next;
  }
}

void BM_Render_Animacao_render(BM_ANIMACAO *aux)
{
  int sourceX = aux->sprite->image->width * aux->frameAtualColuna;
  int sourceY = aux->sprite->image->height * aux->frameAtualLinha;
  bm_render_region_scaled(aux->sprite, sourceX, sourceY, aux->destinoX, aux->destinoY, aux->destinoW, aux->destinoH, 0);
  if (aux->render == 1)
  {
    aux->render = 2;
    BM_Animacao_avancar(aux);
  }
}

void BM_Render_Animacao_checar(BM_ANIMACAO *aux)
{
  if (aux->finalizado == 1)
  {
    BM_Animacao_remover(aux);
  }
}