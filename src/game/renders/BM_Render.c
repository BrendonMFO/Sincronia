#include "BM_Render.h"

void BM_Render_inicial()
{
  bm_render_add_callback(BM_Render_campo_background, NULL);
  bm_render_add_callback(BM_Render_campo, NULL);
  bm_render_add_callback(BM_Render_player, NULL);
  bm_render_add_callback(BM_Render_player_ia, NULL);
  bm_render_add_callback(BM_Render_animacao, NULL);
  bm_render_add_callback(BM_Render_tutorial, NULL);
}