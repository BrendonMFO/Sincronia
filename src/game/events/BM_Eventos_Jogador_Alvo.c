//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Eventos.h"
#include "BM_Hexagono.h"
#include "BM_Oponente.h"
#include "BM_Core_Eventos.h"
#include "BM_Allegro_eventos.h"
#include "BM_Communication_Send.h"
#include "BM_Allegro_eventos_mouse.h"
#include "BM_Allegro_eventos_funcoes.h"

//==========================================================================
// Prototipos
//==========================================================================
void BM_Eventos_Jogador_Alvo_voltar();
void BM_Eventos_Jogador_Alvo_empate();
void BM_Eventos_Jogador_Alvo_click(int, int);
void BM_Eventos_Jogador_Alvo_vitoria_ataque(BM_HEXAGONO *);
void BM_Eventos_Jogador_Alvo_vitoria_defesa(BM_HEXAGONO *);
void BM_Evento_Jogador_Alvo(ALLEGRO_EVENT event, void *_parametro);

/**
 * @brief 
 * - Função que será executada sempre que o EVENTO JOGADOR
 *   for chamado 
 */
void BM_Evento_Jogador_alvo_registrar()
{
    BM_Eventos_adicionar_funcao(BM_Evento_Jogador_Alvo, NULL);
}

/**
 * @brief 
 * - Função responsavel por tratar os eventos da engine para o controle
 *   de alvo
 */
void BM_Evento_Jogador_Alvo(ALLEGRO_EVENT event, void *_parametro)
{
    switch (event.type)
    {
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        return BM_Eventos_Jogador_Alvo_click(event.mouse.x, event.mouse.y);

    case ALLEGRO_EVENT_KEY_DOWN:
        switch (event.keyboard.keycode)
        {
        case ALLEGRO_KEY_A:
            return BM_Eventos_Jogador_Alvo_voltar();
        }
    }
}

/**
 * @brief 
 * - Função responsavel por encerrar o controle de seleção de alvos
 */
void BM_Eventos_Jogador_Alvo_voltar()
{
    BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

    BM_Hexagono_desmarcar_sincronia(JOGADOR);

    BM_Eventos_Funcoes_remover(BM_Evento_Jogador_Alvo);

    BM_Evento_Jogador_registrar();

    BM_Communication_Send_toggle_sincronia(0);
}

/**
 * @brief 
 * - Função responsavel por tratar qual hexagono o jogador selecionou e executar
 *   a função de batalha para definir a sequencia de eventos do jogo
 */
void BM_Eventos_Jogador_Alvo_click(int x, int y)
{
    BM_HEXAGONO *hexagonoClick = BM_Hexagono_click(x, y);

    if (hexagonoClick == NULL || hexagonoClick->estado != ADVERSARIO || hexagonoClick->alvo == 0)
        return;

    BM_Communication_Send_battle(hexagonoClick->id);

    switch (BM_Hexagono_batalha(hexagonoClick->id, BM_Player_getJogador()->hexagonoAtual, JOGADOR, ADVERSARIO))
    {
    case VITORIA_ATAQUE:
        BM_Eventos_Jogador_Alvo_vitoria_ataque(hexagonoClick);
        break;

    case VITORIA_DEFESA:
        BM_Eventos_Jogador_Alvo_vitoria_defesa(hexagonoClick);
        break;

    case EMPATE:
        BM_Eventos_Jogador_Alvo_empate();
        break;
    }

    BM_Eventos_Funcoes_remover(BM_Evento_Jogador_Alvo);
}

/**
 * @brief 
 * 
 */
void BM_Eventos_Jogador_Alvo_empate()
{
    BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

    BM_Hexagono_desmarcar_sincronia(JOGADOR);
}

/**
 * @brief 
 * 
 */
void BM_Eventos_Jogador_Alvo_vitoria_ataque(BM_HEXAGONO *hexagonoClick)
{
    BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

    BM_Hexagono_desmarcar_sincronia(JOGADOR);

    BM_Player_getJogador()->hexagonoAtual = hexagonoClick->id;

    BM_Communication_Send_move_player(hexagonoClick->id);

    BM_Player_getJogador()->quantidadeTerritorio++;

    BM_Player_getOpponentPlayer()->quantidadeTerritorio--;

    hexagonoClick->estado = JOGADOR;
}

/**
 * @brief 
 * 
 */
void BM_Eventos_Jogador_Alvo_vitoria_defesa(BM_HEXAGONO *hexagonoClick)
{
    BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);

    BM_Hexagono_desmarcar_sincronia(JOGADOR);

    BM_Player_getJogador()->quantidadeTerritorio--;

    BM_Player_getOpponentPlayer()->quantidadeTerritorio++;

    BM_Campo_getCampo()->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado = ADVERSARIO;
}
