#include "bm_display.h"

static BM_DISPLAY display;

BM_DISPLAY bm_get_display()
{
  return display;
}

void bm_display_init(int _width, int _height)
{
  display.width = _width;
  display.height = _height;
}