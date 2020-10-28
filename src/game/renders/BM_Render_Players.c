#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Recursos.h"
#include "BM_Oponente.h"

void BM_Render_player()
{
  int destinoX, destinoY;
  destinoX = (SPRITES(BM_IMG_PLAYER)->imagem->width / 2) + BM_Campo_getCampo()->hexagonos[BM_Player_getJogador()->hexagonoAtual].posicaoX;
  destinoY = (SPRITES(BM_IMG_PLAYER)->imagem->height / 6) + BM_Campo_getCampo()->hexagonos[BM_Player_getJogador()->hexagonoAtual].posicaoY;
  BM_Render_normal(SPRITES(BM_IMG_PLAYER), destinoX, destinoY, 0);
}

void BM_Render_player_ia()
{
  int destinoX, destinoY;
  destinoX = (SPRITES(BM_IMG_PLAYER_IA)->imagem->width / 2) + BM_Campo_getCampo()->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual].posicaoX;
  destinoY = (SPRITES(BM_IMG_PLAYER_IA)->imagem->height / 6) + BM_Campo_getCampo()->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual].posicaoY;
  BM_Render_normal(SPRITES(BM_IMG_PLAYER_IA), destinoX, destinoY, 0);
}