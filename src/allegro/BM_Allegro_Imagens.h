#ifndef _BM_ALLEGRO_IMAGENS_
#define _BM_ALLEGRO_IMAGENS_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//==========================================================================
// Estrutura de dados das imagens
//==========================================================================
typedef struct BM_IMAGEM_S
{
	ALLEGRO_BITMAP *bitmap;
	int frame_largura;
	int frame_altura;
	int sprite_linhas;
	int sprite_colunas;
} BM_IMAGEM;

//==========================================================================
// Carregar imagem
//==========================================================================
BM_IMAGEM *BM_Allegro_carregar_imagem(char *img_path, int _framesLinhas, int _framesColunas);

//==========================================================================
// Retornar largura de um bitmap
//==========================================================================
int BM_Allegro_largura_da_imagem(ALLEGRO_BITMAP *_imagem);

//==========================================================================
// Retornar altura de um bitmap
//==========================================================================
int BM_Allegro_altura_da_imagem(ALLEGRO_BITMAP *_imagem);

#endif