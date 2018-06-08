//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#ifndef _BM_MAIN_RENDERS_
#define _BM_MAIN_RENDERS_

#include "BM_Allegro.h"
#include "BM_Recursos_Conteudo.h"

//==========================================================================
// Macros
//==========================================================================
#define RENDER_DADOS_REGIAO int _sX, int _sY, int _dX, int _dY

//==========================================================================
// Typedef's
//==========================================================================
typedef void (*BM_RENDER_FUNCAO)(void *);

//==========================================================================
// Estrutura de dados de fun��es para renderizar elementos
//==========================================================================
typedef struct BM_RENDER_S
{
	int ativo;
	BM_RENDER_FUNCAO funcao;
	void *parametro;
	struct BM_RENDER_S *anterior;
	struct BM_RENDER_S *proximo;
} BM_RENDER;

//==========================================================================
// Fila de dados de fun��es para renderiza��o
//==========================================================================
typedef struct BM_RENDER_FILA_S
{
	BM_RENDER *inicio;
	BM_RENDER *fim;
} BM_RENDER_FILA;

//==========================================================================
// Iniciar fila de renderiza��o
//==========================================================================
int BM_Render_iniciar_fila();

//==========================================================================
// Adicionar fun��o na fila de renderiza��o
//==========================================================================
void BM_Render_adicionar_funcao(BM_RENDER_FUNCAO _funcao, void *_parametro);

//==========================================================================
// Remover fun��o da fila de renderiza��o
//==========================================================================
void BM_Render_remover_funcao(BM_RENDER_FUNCAO _funcao);

//==========================================================================
// Processo de renderização de uma imagem completa
//==========================================================================
void BM_Render_normal(BM_SPRITES *_sprite, int _x, int _y, int _flag);

//==========================================================================
// Processo de renderização de parte de uma imagem escalonada
//==========================================================================
void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag);

//==========================================================================
// Processo de renderização de parte de uma imagem
//==========================================================================
void BM_Render_regiao(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _flag);

//==========================================================================
// Processo de renderização de parte de uma imagem escalonada
//==========================================================================
void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag);

//==========================================================================
// Loop de renderização principal
//==========================================================================
void BM_Render_loop();

/**
 * @brief 
 * - Função que é chamada no inicio do processo de renderização da engine
 */
void BM_Render_inicial();

#endif