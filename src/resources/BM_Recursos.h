#ifndef _BM_RESOURCES_
#define _BM_RESOURCES_

#include "BM_Recursos_Conteudo.h"
#include "BM_Allegro.h"

#ifdef DEBUG
	#define RESOURCE(NAME) "./Recursos/"NAME""
#else
	#define RESOURCE(NAME) "../public/"NAME""
#endif

//==========================================================================
// Constantes
//==========================================================================
#define ERRO 0
#define SUCESSO 1
#define QUANTIDADE_SPRITES 12
#define QUANTIDADE_TUTORIAL 10
#define QUANTIDADE_FONTES 2
#define SPRITES(INDICE) BM_Recursos_obter_recurso((INDICE))

//==========================================================================
// Obter array com os recursos visuais carregados
//==========================================================================
BM_SPRITES *BM_Recursos_obter_recurso(int _indice);

//==========================================================================
// Obter fonte
//==========================================================================
ALLEGRO_FONT *BM_Recursos_obter_fonte(int _indice);

//==========================================================================
// Obter sprite do tutorial
//==========================================================================
BM_SPRITES *BM_Recursos_obter_tutorial(int _indice);

//==========================================================================
// Carregar Sprites
//==========================================================================
int BM_Recursos_carregar_recursos();

//==========================================================================
// Destruir arquivos
//==========================================================================
void BM_Recursos_destruir();

#endif