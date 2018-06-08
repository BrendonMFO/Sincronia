//======================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//======================================================================

#ifndef _BM_RESOURCES_CONTEUDO_
#define _BM_RESOURCES_CONTEUDO_

#include "BM_Allegro_Imagens.h"

//==========================================================================
// Definir constantes
//==========================================================================
#define Imagem imagem->bitmap

//==========================================================================
// Estrutura de dados dos sprites
//==========================================================================
typedef struct BM_SPRITES_S
{
	BM_IMAGEM *imagem;
	int ajusteW;
	int ajusteH;
} BM_SPRITES;

//==========================================================================
// ENUM - Enumeração dos sprites disponiveis
//==========================================================================
enum ENUM_SPRITES
{
	BM_IMG_MAPA_01,
	BM_IMG_HEXAGONO,
	BM_IMG_PLAYER,
	BM_IMG_HEXAGONO_ALVO,
	BM_IMG_ELEMENTOS,
	BM_IMG_PLAYER_IA,
	BM_ANI_LUZ,
	BM_ANI_TREVAS,
	BM_ANI_FOGO,
	BM_ANI_AGUA,
	BM_ANI_TERRA,
	BM_ANI_AR
};

//==========================================================================
// ENUM = Enumeração das fontes disponiveis
//==========================================================================
enum ENUM_FONTES
{
	BM_FONTE_ALBA,
	BM_FONTE_ALBA_MENOR
};

#endif