#ifndef _BM_RESOURCES_CONTEUDO_
#define _BM_RESOURCES_CONTEUDO_

#include "bm_allegro_bitmap.h"

#define Imagem image->bitmap

typedef struct BM_SPRITES_S
{
  BM_ALLEGRO_BITMAP *image;
  int ajusteW;
  int ajusteH;
} BM_SPRITES;

enum ENUM_SPRITES
{
  BM_IMG_MAPA_01,
  BM_IMG_HEXAGONO,
  BM_IMG_PLAYER,
  BM_IMG_HEXAGONO_ALVO,
  BM_IMG_ELEMENTOS,
  BM_IMG_PLAYER_IA,
  BM_ANI_LUZ,
  BM_ANI_TREVAS,
  BM_ANI_FOGO,
  BM_ANI_AGUA,
  BM_ANI_TERRA,
  BM_ANI_AR
};

enum ENUM_FONTES
{
  BM_FONTE_ALBA,
  BM_FONTE_ALBA_MENOR
};

#endif