//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Rodadas.h"
#include "BM_Oponente.h"
#include "BM_Core_Eventos.h"
#include "BM_Allegro_eventos.h"

//==========================================================================
// Prototipos
//==========================================================================
void BM_Eventos_Jogo_reiniciar();
void BM_Eventos_Jogo_Executando();
void BM_Eventos_Jogo_verificar_fim(ALLEGRO_EVENT, void *_parameter);

int executando = 0;

/**
 * @brief 
 * - Iniciar jogo
 */
void BM_Eventos_Jogo_registrar()
{
    BM_Eventos_Jogo_Executando();
    BM_Eventos_adicionar_funcao(BM_Eventos_Jogo_verificar_fim, NULL);
    BM_Render_adicionar_funcao(BM_Render_rodada, NULL);
}

/**
 * @brief 
 * - Tratar eventos disparados no sistema
 */
void BM_Eventos_Jogo_eventos(ALLEGRO_EVENT event, void *_parametro)
{
    switch (event.type)
    {
    case ALLEGRO_EVENT_KEY_DOWN:
        switch (event.keyboard.keycode)
        {
        case ALLEGRO_KEY_R:
            return BM_Eventos_Jogo_reiniciar();
        }
    }
}

/**
 * @brief 
 * - Verificar se o jogo possue um vencedor
 */
void BM_Eventos_Jogo_verificar_fim(ALLEGRO_EVENT event, void *_parameter)
{
    if (BM_Rodada_get_restantes() == 0 ||
        BM_Player_getJogador()->quantidadeTerritorio == 0 ||
        BM_Player_getOpponentPlayer()->quantidadeTerritorio == 0)
    {
        BM_Render_adicionar_funcao(BM_Render_resultado, NULL);
        BM_Eventos_adicionar_funcao(BM_Eventos_Jogo_eventos, NULL);
        BM_Eventos_Funcoes_remover(BM_Eventos_Jogo_verificar_fim);
        executando = 0;
    }
}

/**
 * @brief 
 * - Verificar se o jogo já foi iniciado, se não iniciar as operações
 */
void BM_Eventos_Jogo_Executando()
{
    if (executando == 0)
    {
        BM_Rodada_set(50);
        executando = 1;
    }
}

/**
 * @brief 
 * - Reiniciar jogo
 */
void BM_Eventos_Jogo_reiniciar()
{
    BM_Campo_redefinir();
    BM_Oponente_iniciar_valores(BM_Campo_getCampo()->quantidade - 1);
    BM_Eventos_Funcoes_remover(BM_Eventos_Jogo_eventos);
    BM_Render_remover_funcao(BM_Render_resultado);
    BM_Eventos_Jogo_registrar();
}