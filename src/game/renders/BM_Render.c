#include "BM_Render.h"

void BM_Render_inicial()
{
  BM_Render_adicionar_funcao(BM_Render_campo_background, NULL);
  BM_Render_adicionar_funcao(BM_Render_campo, NULL);
  BM_Render_adicionar_funcao(BM_Render_player, NULL);
  BM_Render_adicionar_funcao(BM_Render_player_ia, NULL);
  BM_Render_adicionar_funcao(BM_Render_animacao, NULL);
  BM_Render_adicionar_funcao(BM_Render_tutorial, NULL);
}