#ifndef _BM_RESOURCES_
#define _BM_RESOURCES_

#include "bm_allegro.h"
#include "BM_Recursos_Conteudo.h"

#define RESOURCE(NAME) "../public/" NAME ""

#define QUANTIDADE_FONTES 2
#define QUANTIDADE_IMAGENS 11
#define QUANTIDADE_SPRITES 12
#define SPRITES(INDICE) BM_Recursos_obter_recurso((INDICE))

BM_SPRITES *BM_Recursos_obter_recurso(int _indice);

ALLEGRO_FONT *BM_Recursos_obter_fonte(int _indice);

BM_SPRITES *BM_Recursos_obter_imagem(int _indice);

int BM_Recursos_carregar_recursos();

void BM_Recursos_destruir();

#endif