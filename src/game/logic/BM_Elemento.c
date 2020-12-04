#include "BM_Elemento.h"
#include "BM_Recursos.h"
#include "bm_allegro_mouse_callback_queue.h"

void BM_Elemento_adicionar_mouse_listener()
{
  int sourceW, sourceH, destinoX, i;
  for (i = 0; i < 6; i++)
  {
    int *id = (int *)malloc(sizeof(int));
    *id = i + 1;
    sourceW = bm_al_bitmap_width(SPRITES(BM_IMG_ELEMENTOS)->Imagem) / SPRITES(BM_IMG_ELEMENTOS)->image->columns;
    sourceH = bm_al_bitmap_height(SPRITES(BM_IMG_ELEMENTOS)->Imagem) / SPRITES(BM_IMG_ELEMENTOS)->image->lines;
    destinoX = 196 + (sourceW * i);
    bm_al_mouse_callback_queue_add(NULL, destinoX, 266, destinoX + sourceW, 266 + sourceH, id);
  }
}

void BM_Elemento_remover_mouse_listener()
{
  int sourceW, sourceH, sourceX, destinoX, i;
  for (i = 0; i < 6; i++)
  {
    sourceW = bm_al_bitmap_width(SPRITES(BM_IMG_ELEMENTOS)->Imagem) / SPRITES(BM_IMG_ELEMENTOS)->image->columns;
    sourceH = bm_al_bitmap_height(SPRITES(BM_IMG_ELEMENTOS)->Imagem) / SPRITES(BM_IMG_ELEMENTOS)->image->lines;
    sourceX = sourceW * i;
    destinoX = 196 + (sourceW * i);
    bm_al_mouse_callback_queue_remove(destinoX, 266, destinoX + sourceX, 266 + sourceH);
  }
}