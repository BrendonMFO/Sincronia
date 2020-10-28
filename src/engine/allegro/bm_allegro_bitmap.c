#include "bm_allegro_bitmap.h"

BM_ALLEGRO_BITMAP *bm_al_load_bitmap(char *img_path, int _lines, int _columns)
{
  BM_ALLEGRO_BITMAP *newBitmap = (BM_ALLEGRO_BITMAP *)malloc(sizeof(BM_ALLEGRO_BITMAP));
  newBitmap->bitmap = al_load_bitmap(img_path);

  if (!newBitmap->bitmap)
  {
    return NULL;
  }

  newBitmap->width = bm_al_bitmap_width(newBitmap->bitmap) / _columns;
  newBitmap->height = bm_al_bitmap_height(newBitmap->bitmap) / _lines;
  newBitmap->lines = _lines;
  newBitmap->columns = _columns;

  return newBitmap;
}

int bm_al_bitmap_width(ALLEGRO_BITMAP *_imagem)
{
  return al_get_bitmap_width(_imagem);
}

int bm_al_bitmap_height(ALLEGRO_BITMAP *_imagem)
{
  return al_get_bitmap_height(_imagem);
}