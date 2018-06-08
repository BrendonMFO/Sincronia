//======================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//======================================================================

#include "BM_Campo.h"
#include "BM_Recursos.h"
#include "BM_Core_Renders.h"

//======================================================================
// Prototipos
//======================================================================
void BM_Render_hexagono(BM_HEXAGONO _hexagono);

/**
 * @brief 
 * - Função responsavel por renderizar a imagem de background do cenario
 */
void BM_Render_campo_background()
{
	BM_Render_normal(SPRITES(BM_IMG_MAPA_01), 0, 0, 0);
}

/**
 * @brief 
 * - Iniciar renderização de todos os hexagonos
 */
void BM_Render_campo()
{
	int i;
	BM_Campo *campo = BM_Campo_getCampo();
	for (i = 0; i < campo->quantidade; i++)
	{
		BM_Render_hexagono(campo->hexagonos[i]);
	}
}

/**
 * @brief 
 * - Renderizar cada hexagono na posição correta
 * 
 * @param _hexagono 
 * - Hexagono que será renderizado
 */
void BM_Render_hexagono(BM_HEXAGONO _hexagono)
{
	int sourceX, sourceY, sourceW;

	sourceW = BM_Allegro_largura_da_imagem(SPRITES(BM_IMG_HEXAGONO)->Imagem) / SPRITES(BM_IMG_HEXAGONO)->imagem->sprite_colunas;
	sourceX = SPRITES(BM_IMG_HEXAGONO)->imagem->frame_largura * _hexagono.estado;

	if (_hexagono.visivel == 1 || _hexagono.estado == JOGADOR)
		sourceY = SPRITES(BM_IMG_HEXAGONO)->imagem->frame_altura * _hexagono.elemento;
	else
		sourceY = 0;

	BM_Render_regiao(SPRITES(BM_IMG_HEXAGONO), sourceX, sourceY, _hexagono.posicaoX, _hexagono.posicaoY, 0);

	if (_hexagono.alvo != HEXAGONO_NORMAL)
		BM_Render_regiao(SPRITES(BM_IMG_HEXAGONO_ALVO), sourceW * (_hexagono.alvo - 1), 0, _hexagono.posicaoX, _hexagono.posicaoY, 0);
}