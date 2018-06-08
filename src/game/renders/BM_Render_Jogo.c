#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Rodadas.h"
#include "BM_Recursos.h"
#include "BM_Tutorial.h"
#include "BM_Oponente.h"
#include "BM_Allegro_janela.h"

/**
 * @brief 
 * - Renderizar tutorial
 */
void BM_Render_tutorial()
{
	al_draw_filled_rectangle(0, 0, BM_Janela_obter_dados().largura, BM_Janela_obter_dados().altura, al_map_rgba(0, 0, 0, 220));
	BM_Render_normal(BM_Recursos_obter_imagem(BM_Render_obter_tutorial()), 0, 0, 0);
}

/**
 * @brief 
 * - Renderizar tela de aguargando oponente
 */
void BM_Render_esperando_oponente()
{
	al_draw_filled_rectangle(0, 0, BM_Janela_obter_dados().largura, BM_Janela_obter_dados().altura, al_map_rgba(0, 0, 0, 220));
	BM_Render_normal(BM_Recursos_obter_imagem(10), 0, 0, 0);
}

/**
 * @brief 
 * - Renderizar elementos
 */
void BM_Render_elementos()
{
	int sourceW, sourceH, sourceX, destinoX, i, *elemento;
	al_draw_filled_rectangle(0, 0, BM_Janela_obter_dados().largura, BM_Janela_obter_dados().altura, al_map_rgba(0, 0, 0, 150));
	elemento = &BM_Player_getJogador()->elementosDisponivel.luz;
	sourceW = SPRITES(BM_IMG_ELEMENTOS)->imagem->frame_largura;
	sourceH = SPRITES(BM_IMG_ELEMENTOS)->imagem->frame_altura;

	for (i = 0; i <= 6; i++, elemento++)
	{
		sourceX = sourceW * i;
		destinoX = (196) + (sourceW * i);
		if (*elemento == 1)
			al_draw_scaled_bitmap(SPRITES(BM_IMG_ELEMENTOS)->Imagem, sourceX, 0, sourceW, sourceH, BM_AJUSTE_XW(destinoX), BM_AJUSTE_YH(266), SPRITES(BM_IMG_ELEMENTOS)->ajusteW, SPRITES(BM_IMG_ELEMENTOS)->ajusteH, 0);
		else
			al_draw_tinted_scaled_bitmap(SPRITES(BM_IMG_ELEMENTOS)->Imagem, al_map_rgb(100, 100, 100), sourceX, 0, sourceW, sourceH, BM_AJUSTE_XW(destinoX), BM_AJUSTE_YH(266), SPRITES(BM_IMG_ELEMENTOS)->ajusteW, SPRITES(BM_IMG_ELEMENTOS)->ajusteH, 0);
	}

	al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA_MENOR), al_map_rgb(255, 200, 200), BM_AJUSTE_XW(1300), BM_AJUSTE_YH(800), ALLEGRO_ALIGN_LEFT, "ESC - Voltar", BM_Rodada_get_restantes());
}

/**
 * @brief 
 * - Renderizar Rodadas
 */
void BM_Render_rodada()
{
	al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA_MENOR), al_map_rgb(225, 225, 225), BM_AJUSTE_XW(1000), BM_AJUSTE_YH(850), ALLEGRO_ALIGN_LEFT, "A - Atacar S - Adicionar T - Tutorial", BM_Rodada_get_restantes());
	al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 200, 200), BM_AJUSTE_XW(100), BM_AJUSTE_YH(10), ALLEGRO_ALIGN_CENTRE, "%d", BM_Rodada_get_restantes());
}

/**
 * @brief 
 * - Renderizar resultado
 */
void BM_Render_resultado()
{
	char texto[10];
	int ia = BM_Player_getOpponentPlayer()->quantidadeTerritorio;
	int jogador = BM_Player_getJogador()->quantidadeTerritorio;

	al_draw_filled_rectangle(0, 0, BM_Janela_obter_dados().largura, BM_Janela_obter_dados().altura, al_map_rgba(0, 0, 0, 150));
    
	if (jogador > ia)
		strcpy(texto, "Vitoria");
	else if (jogador < ia)
		strcpy(texto, "Derrota");
	else
		strcpy(texto, "Empate");

	al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(220, 220, 220), BM_AJUSTE_XW(800), BM_AJUSTE_YH(125), ALLEGRO_ALIGN_CENTRE, "%s", texto);
	al_draw_scaled_bitmap(SPRITES(BM_IMG_HEXAGONO)->Imagem, 238, 0, SPRITES(BM_IMG_HEXAGONO)->imagem->frame_largura, SPRITES(BM_IMG_HEXAGONO)->imagem->frame_altura, BM_AJUSTE_XW(323), BM_AJUSTE_YH(326), SPRITES(BM_IMG_HEXAGONO)->ajusteW, SPRITES(BM_IMG_HEXAGONO)->ajusteH, 0);
	al_draw_scaled_bitmap(SPRITES(BM_IMG_HEXAGONO)->Imagem, 476, 0, SPRITES(BM_IMG_HEXAGONO)->imagem->frame_largura, SPRITES(BM_IMG_HEXAGONO)->imagem->frame_altura, BM_AJUSTE_XW(1065), BM_AJUSTE_YH(326), SPRITES(BM_IMG_HEXAGONO)->ajusteW, SPRITES(BM_IMG_HEXAGONO)->ajusteH, 0);
	al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 255, 255), BM_AJUSTE_XW(435), BM_AJUSTE_YH(350), ALLEGRO_ALIGN_CENTRE, "%d", jogador);
	al_draw_textf(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 255, 255), BM_AJUSTE_XW(1185), BM_AJUSTE_YH(350), ALLEGRO_ALIGN_CENTRE, "%d", ia);
	al_draw_text(BM_Recursos_obter_fonte(BM_FONTE_ALBA), al_map_rgb(255, 255, 255), BM_AJUSTE_XW(800), BM_AJUSTE_YH(700), ALLEGRO_ALIGN_CENTRE, "R - Reiniciar");
}