#ifndef _BM_ALLEGRO_BITMAP_
#define _BM_ALLEGRO_BITMAP_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct BM_IMAGEM_S
{
  ALLEGRO_BITMAP *bitmap;
  int width;
  int height;
  int lines;
  int columns;
} BM_ALLEGRO_BITMAP;

BM_ALLEGRO_BITMAP *bm_al_load_bitmap(char *img_path, int _lines, int _columns);

int bm_al_bitmap_width(ALLEGRO_BITMAP *_imagem);

int bm_al_bitmap_height(ALLEGRO_BITMAP *_imagem);

#endif