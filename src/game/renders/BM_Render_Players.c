#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Recursos.h"
#include "BM_Oponente.h"

void BM_Render_player()
{
  int destinoX, destinoY;
  destinoX = (SPRITES(BM_IMG_PLAYER)->image->width / 2) + bm_field_get()->hexagonos[BM_Player_getJogador()->hexagonoAtual].posicaoX;
  destinoY = (SPRITES(BM_IMG_PLAYER)->image->height / 6) + bm_field_get()->hexagonos[BM_Player_getJogador()->hexagonoAtual].posicaoY;
  bm_render_normal(SPRITES(BM_IMG_PLAYER), destinoX, destinoY, 0);
}

void BM_Render_player_ia()
{
  int destinoX, destinoY;
  destinoX = (SPRITES(BM_IMG_PLAYER_IA)->image->width / 2) + bm_field_get()->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual].posicaoX;
  destinoY = (SPRITES(BM_IMG_PLAYER_IA)->image->height / 6) + bm_field_get()->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual].posicaoY;
  bm_render_normal(SPRITES(BM_IMG_PLAYER_IA), destinoX, destinoY, 0);
}