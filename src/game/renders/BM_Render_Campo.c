#include "BM_Campo.h"
#include "BM_Recursos.h"
#include "BM_Core_Renders.h"

void BM_Render_hexagono(BM_HEXAGONO _hexagono);

void BM_Render_campo_background()
{
  BM_Render_normal(SPRITES(BM_IMG_MAPA_01), 0, 0, 0);
}

void BM_Render_campo()
{
  int i;
  BM_Campo *campo = BM_Campo_getCampo();
  for (i = 0; i < campo->quantidade; i++)
  {
    BM_Render_hexagono(campo->hexagonos[i]);
  }
}

void BM_Render_hexagono(BM_HEXAGONO _hexagono)
{
  int sourceX, sourceY, sourceW;

  sourceW = bm_al_bitmap_width(SPRITES(BM_IMG_HEXAGONO)->Imagem) / SPRITES(BM_IMG_HEXAGONO)->imagem->columns;
  sourceX = SPRITES(BM_IMG_HEXAGONO)->imagem->width * _hexagono.estado;
  sourceY = _hexagono.visivel == 1 || _hexagono.estado == JOGADOR
                ? SPRITES(BM_IMG_HEXAGONO)->imagem->height * _hexagono.elemento
                : 0;

  BM_Render_regiao(SPRITES(BM_IMG_HEXAGONO), sourceX, sourceY, _hexagono.posicaoX, _hexagono.posicaoY, 0);

  if (_hexagono.alvo != HEXAGONO_NORMAL)
  {
    BM_Render_regiao(SPRITES(BM_IMG_HEXAGONO_ALVO), sourceW * (_hexagono.alvo - 1), 0, _hexagono.posicaoX, _hexagono.posicaoY, 0);
  }
}