#include "BM_Campo.h"
#include "BM_Recursos.h"
#include "bm_core_render.h"

void BM_Render_hexagono(BM_HEXAGONO _hexagono);

void BM_Render_campo_background()
{
  bm_render_normal(SPRITES(BM_IMG_MAPA_01), 0, 0, 0);
}

void BM_Render_campo()
{
  int i;
  BM_Campo *campo = bm_field_get();
  for (i = 0; i < campo->quantidade; i++)
  {
    BM_Render_hexagono(campo->hexagonos[i]);
  }
}

void BM_Render_hexagono(BM_HEXAGONO _hexagono)
{
  int sourceX, sourceY, sourceW;

  sourceW = bm_al_bitmap_width(SPRITES(BM_IMG_HEXAGONO)->Imagem) / SPRITES(BM_IMG_HEXAGONO)->image->columns;
  sourceX = SPRITES(BM_IMG_HEXAGONO)->image->width * _hexagono.estado;
  sourceY = _hexagono.visivel == 1 || _hexagono.estado == JOGADOR
                ? SPRITES(BM_IMG_HEXAGONO)->image->height * _hexagono.elemento
                : 0;

  bm_render_region(SPRITES(BM_IMG_HEXAGONO), sourceX, sourceY, _hexagono.posicaoX, _hexagono.posicaoY, 0);

  if (_hexagono.alvo != HEXAGONO_NORMAL)
  {
    bm_render_region(SPRITES(BM_IMG_HEXAGONO_ALVO), sourceW * (_hexagono.alvo - 1), 0, _hexagono.posicaoX, _hexagono.posicaoY, 0);
  }
}