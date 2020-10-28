#ifndef _BM_WINDOW_
#define _BM_WINDOW_

#define BM_FIX_XW(X) ((X)*bm_get_display().width) / 1600
#define BM_FIX_YH(Y) ((Y)*bm_get_display().height) / 920

typedef struct BM_JANELA_S
{
  int width;
  int height;
} BM_DISPLAY;

BM_DISPLAY bm_get_display();

void bm_display_init(int _width, int _height);

#endif