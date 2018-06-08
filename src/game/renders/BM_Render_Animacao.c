//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Core_Renders.h"
#include "BM_Recursos_Animacao.h"

void BM_Render_Animacao_render(BM_ANIMACAO *aux);
void BM_Render_Animacao_checar(BM_ANIMACAO *aux);

/**
 * @brief 
 * - Função responsavel por renderizar todas as animações que estão
 *   pendentes na fila de animações
 */
void BM_Render_animacao()
{
    BM_ANIMACAO *aux;

    for (aux = BM_Animacao_obter_fila()->inicio; aux != NULL; aux = aux->proximo)
    {
        BM_Render_Animacao_render(aux);
    }

    for (aux = BM_Animacao_obter_fila()->inicio; aux != NULL; aux = aux->proximo)
    {
        BM_Render_Animacao_checar(aux);
    }
}

/**
 * @brief 
 * - Função responsavel por renderizar uma animação e avançar o contador
 *   da mesma
 * 
 * @param aux 
 * - Animação que será renderizada
 */
void BM_Render_Animacao_render(BM_ANIMACAO *aux)
{
    int sourceX = aux->sprite->imagem->frame_largura * aux->frameAtualColuna;
    int sourceY = aux->sprite->imagem->frame_altura * aux->frameAtualLinha;
    BM_Render_regiao_escalonada(aux->sprite, sourceX, sourceY, aux->destinoX, aux->destinoY, aux->destinoW, aux->destinoH, 0);
    if (aux->render == SIM)
    {
        aux->render = NAO;
        BM_Animacao_avancar(aux);
    }
}

/**
 * @brief 
 * - Função responsavel por verificar se uma animação chegou a fim,
 *   caso sim, a mesma será removida
 * 
 * @param aux 
 */
void BM_Render_Animacao_checar(BM_ANIMACAO *aux)
{
    if (aux->finalizado != SIM)
    {
        aux = aux->proximo;
        return;
    }

    if (aux->proximo != NULL)
    {
        aux = aux->proximo;
        BM_Animacao_remover(aux->anterior);
        return;
    }

    BM_Animacao_remover(aux);
}