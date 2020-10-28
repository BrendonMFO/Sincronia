#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Rodadas.h"
#include "BM_Recursos.h"
#include "BM_Tutorial.h"
#include "BM_Oponente.h"
#include "bm_display.h"

void BM_Render_tutorial()
{
  al_draw_filled_rectangle(0, 0, bm_get_display().width, bm_get_display().height, al_map_rgba(0, 0, 0, 220));
  BM_Render_normal(BM_Recursos_obter_imagem(BM_Render_obter_tutorial()), 0, 0, 0);
}

void BM_Render_esperando_oponente()
{
  al_draw_filled_rectangle(0, 0, bm_get_display().width, bm_get_display().height, al_map_rgba(0, 0, 0, 220));
  BM_Render_normal(BM_Recursos_obter_imagem(10), 0, 0, 0);
}

void BM_Render_elementos()
{
  int sourceW, sourceH, sourceX, destinoX, i, *elemento;
  al_draw_filled_rectangle(0, 0, bm_get_display().width, bm_get_display().height, al_map_rgba(0, 0, 0, 150));
  elemento = &BM_Player_getJogador()->elementosDisponivel.luz;
  sourceW = SPRITES(BM_IMG_ELEMENTOS)->imagem->width;
  sourceH = SPRITES(BM_IMG_ELEMENTOS)->imagem->height;

  for (i = 0; i <= 6; i++, elemento++)
  {
    sourceX = sourceW * i;
    destinoX = (196) + (sourceW * i);
    if (*elemento == 1)
    {
      al_draw_scaled_bitmap(SPRITES(BM_IMG_ELEMENTOS)->Imagem, sourceX, 0, sourceW, sourceH, BM_FIX_XW(destinoX), BM_FIX_YH(266), SPRITES(BM_IMG_ELEMENTOS)->ajusteW, SPRITES(BM_IMG_ELEMENTOS)->ajusteH, 0);
    }
    else
    {
      al_draw_tinted_scaled_bitmap(SPRITES(BM_IMG_ELEMENTOS)->Imagem, al_map_rgb(100, 100, 100), sourceX, 0, sourceW, sourceH, BM_FIX_XW(destinoX), BM_FIX_YH(266), SPRITES(BM_IMG_ELEMENTOS)->ajusteW, SPRITES(BM_IMG_ELEMENTOS)->ajusteH, 0);
    }
  }

  al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA_MENOR), al_map_rgb(255, 200, 200), BM_FIX_XW(1300), BM_FIX_YH(800), ALLEGRO_ALIGN_LEFT, "ESC - Voltar", BM_Rodada_get_restantes());
}

void BM_Render_rodada()
{
  al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA_MENOR), al_map_rgb(225, 225, 225), BM_FIX_XW(1000), BM_FIX_YH(850), ALLEGRO_ALIGN_LEFT, "A - Atacar S - Adicionar T - Tutorial", BM_Rodada_get_restantes());
  al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 200, 200), BM_FIX_XW(100), BM_FIX_YH(10), ALLEGRO_ALIGN_CENTRE, "%d", BM_Rodada_get_restantes());
}

void BM_Render_resultado()
{
  char texto[10];
  int ia = BM_Player_getOpponentPlayer()->quantidadeTerritorio;
  int jogador = BM_Player_getJogador()->quantidadeTerritorio;

  al_draw_filled_rectangle(0, 0, bm_get_display().width, bm_get_display().height, al_map_rgba(0, 0, 0, 150));

  if (jogador > ia)
  {
    strcpy(texto, "Vitoria");
  }
  else if (jogador < ia)
  {
    strcpy(texto, "Derrota");
  }
  else
  {
    strcpy(texto, "Empate");
  }

  al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(220, 220, 220), BM_FIX_XW(800), BM_FIX_YH(125), ALLEGRO_ALIGN_CENTRE, "%s", texto);
  al_draw_scaled_bitmap(SPRITES(BM_IMG_HEXAGONO)->Imagem, 238, 0, SPRITES(BM_IMG_HEXAGONO)->imagem->width, SPRITES(BM_IMG_HEXAGONO)->imagem->height, BM_FIX_XW(323), BM_FIX_YH(326), SPRITES(BM_IMG_HEXAGONO)->ajusteW, SPRITES(BM_IMG_HEXAGONO)->ajusteH, 0);
  al_draw_scaled_bitmap(SPRITES(BM_IMG_HEXAGONO)->Imagem, 476, 0, SPRITES(BM_IMG_HEXAGONO)->imagem->width, SPRITES(BM_IMG_HEXAGONO)->imagem->height, BM_FIX_XW(1065), BM_FIX_YH(326), SPRITES(BM_IMG_HEXAGONO)->ajusteW, SPRITES(BM_IMG_HEXAGONO)->ajusteH, 0);
  al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 255, 255), BM_FIX_XW(435), BM_FIX_YH(350), ALLEGRO_ALIGN_CENTRE, "%d", jogador);
  al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 255, 255), BM_FIX_XW(1185), BM_FIX_YH(350), ALLEGRO_ALIGN_CENTRE, "%d", ia);
  al_draw_text(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 255, 255), BM_FIX_XW(800), BM_FIX_YH(700), ALLEGRO_ALIGN_CENTRE, "R - Reiniciar");
}