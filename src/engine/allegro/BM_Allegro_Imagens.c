//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Allegro_Imagens.h"

//==========================================================================
// Carregar imagem
//==========================================================================
BM_IMAGEM *BM_Allegro_carregar_imagem(char *img_path, int _framesLinhas, int _framesColunas)
{
	BM_IMAGEM *temp = (BM_IMAGEM *)malloc(sizeof(BM_IMAGEM));
	temp->bitmap = al_load_bitmap(img_path);

	if (!temp->bitmap)
		return NULL;

	temp->frame_largura = BM_Allegro_largura_da_imagem(temp->bitmap) / _framesColunas;
	temp->frame_altura = BM_Allegro_altura_da_imagem(temp->bitmap) / _framesLinhas;
	temp->sprite_linhas = _framesLinhas;
	temp->sprite_colunas = _framesColunas;

	return temp;
}

//==========================================================================
// Retornar largura
//==========================================================================
int BM_Allegro_largura_da_imagem(ALLEGRO_BITMAP *_imagem)
{
	return al_get_bitmap_width(_imagem);
}

//==========================================================================
// Retornar altura
//==========================================================================
int BM_Allegro_altura_da_imagem(ALLEGRO_BITMAP *_imagem)
{
	return al_get_bitmap_height(_imagem);
}