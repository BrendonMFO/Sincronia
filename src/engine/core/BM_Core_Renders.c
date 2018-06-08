//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Recursos.h"
#include "BM_Utils.h"
#include "BM_Core_Renders.h"
#include "BM_Allegro_janela.h"
#include "BM_Recursos_Conteudo.h"
#include <string.h>

//==========================================================================
// Variaveis
//==========================================================================
BM_RENDER_FILA *renderFila = NULL;

//==========================================================================
// Prototipos para funçães de renders
//==========================================================================
void BM_Render_renderizar_fila();
BM_RENDER *BM_Render_procurar_fila(BM_RENDER_FUNCAO _funcao);
void BM_Render_normal(BM_SPRITES *_sprite, int _x, int _y, int _flag);
void BM_Render_regiao(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _flag);
void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag);

//==========================================================================
// Processo de renderização de uma imagem completa
//==========================================================================
void BM_Render_normal(BM_SPRITES *_sprite, int _x, int _y, int _flag)
{
	al_draw_scaled_bitmap(_sprite->Imagem,
						  0, 0, _sprite->imagem->frame_largura, _sprite->imagem->frame_altura,
						  BM_AJUSTE_XW(_x), BM_AJUSTE_YH(_y), _sprite->ajusteW, _sprite->ajusteH, _flag);
}

//==========================================================================
// Processo de renderização de parte de uma imagem
//==========================================================================
void BM_Render_regiao(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _flag)
{
	al_draw_scaled_bitmap(_sprite->Imagem,
						  _sX, _sY,
						  _sprite->imagem->frame_largura, _sprite->imagem->frame_altura,
						  BM_AJUSTE_XW(_dX), BM_AJUSTE_YH(_dY),
						  _sprite->ajusteW, _sprite->ajusteH, _flag);
}

//==========================================================================
// Processo de renderização de parte de uma imagem escalonada
//==========================================================================
void BM_Render_regiao_escalonada(BM_SPRITES *_sprite, RENDER_DADOS_REGIAO, int _dW, int _dH, int _flag)
{
	al_draw_scaled_bitmap(_sprite->Imagem,
						  _sX, _sY, _sprite->imagem->frame_largura, _sprite->imagem->frame_altura,
						  BM_AJUSTE_XW(_dX), BM_AJUSTE_YH(_dY),
						  BM_AJUSTE_XW(_dW), BM_AJUSTE_YH(_sprite->ajusteH), _flag);
}

//==========================================================================
// Loop de renderização principal
//==========================================================================
void BM_Render_loop()
{
	BM_Render_renderizar_fila();
	al_flip_display();
}

//==========================================================================
// Iniciar fila de renderização
//==========================================================================
int BM_Render_iniciar_fila()
{
	renderFila = (BM_RENDER_FILA *)malloc(1 * sizeof(BM_RENDER_FILA));
	if (renderFila == NULL)
	{
		printf("Erro: Nao foi possivel alocar memoria para a fila de renderizacao\n");
		return 0;
	}
	renderFila->inicio = NULL;
	renderFila->fim = NULL;
	return 1;
}

/**
 * @brief 
 * - Adicionar função na fila de renderização
 * 
 * @param _funcao 
 * - Ponteiro para a nova função que será incluida na fila de renderizações
 * @param _parametro 
 * - Ponteiro para os parametros opcionais da função 
 */
void BM_Render_adicionar_funcao(BM_RENDER_FUNCAO _funcao, void *_parametro)
{
	BM_RENDER *aux = (BM_RENDER *)malloc(1 * sizeof(BM_RENDER));

	BM_Utils_ponteiro(aux, "Erro: Nao foi possivel alocar memoria para uma funcao de renderizacao");

	aux->ativo = 1;
	aux->proximo = NULL;
	aux->funcao = _funcao;
	aux->parametro = _parametro;

	if (renderFila->inicio == NULL)
	{
		renderFila->inicio = aux;
		renderFila->fim = aux;
		aux->anterior = NULL;
	}
	else
	{
		renderFila->fim->proximo = aux;
		aux->anterior = renderFila->fim;
		renderFila->fim = aux;
	}
}

//==========================================================================
// Remover função da fila de renderização
//==========================================================================
void BM_Render_remover_funcao(BM_RENDER_FUNCAO _funcao)
{
	BM_RENDER *aux = BM_Render_procurar_fila(_funcao);
	BM_Utils_ponteiro(aux, "Ponteiro da funcao de renderizacao nao encontrada.");

	aux->ativo = 0;

	if (renderFila->inicio == renderFila->fim)
	{
		renderFila->inicio = NULL;
		renderFila->fim = NULL;
	}
	else
	{
		if (aux->anterior != NULL)
			aux->anterior->proximo = aux->proximo;
		else
			renderFila->inicio = aux->proximo;
		if (aux->proximo != NULL)
			aux->proximo->anterior = aux->anterior;
		else
			renderFila->fim = aux->anterior;
	}

}

//==========================================================================
// Renderizar dados na fila de renderização
//==========================================================================
void BM_Render_renderizar_fila()
{
	BM_RENDER *aux;
	for (aux = renderFila->inicio; aux != NULL; aux = aux->proximo)
		aux->funcao(aux->parametro);
}

//==========================================================================
// Procurar função especifica na fila de renderiação
//==========================================================================
BM_RENDER *BM_Render_procurar_fila(BM_RENDER_FUNCAO _funcao)
{
	BM_RENDER *aux;
	for (aux = renderFila->inicio; aux != NULL; aux = aux->proximo)
	{
		if (aux->funcao == _funcao)
			break;
	}
	return aux;
}