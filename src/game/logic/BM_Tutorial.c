#include "BM_Tutorial.h"
#include "bm_display.h"

static int TUTORIAL = 0;

void BM_Render_avancar_tutorial()
{
  TUTORIAL++;
}

void BM_Render_reiniciar_tutorial()
{
  TUTORIAL = 0;
}

int BM_Render_obter_tutorial()
{
  return TUTORIAL;
}