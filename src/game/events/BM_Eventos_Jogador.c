#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Oponente.h"
#include "BM_Core_Eventos.h"
#include "BM_Allegro_eventos.h"
#include "BM_Communication_Send.h"

//===============================================================================
// Prototipos
//===============================================================================
void BM_Evento_jogador_atacar();
void BM_Evento_jogador_reiniciar();
void BM_Evento_jogador_conquistar();
void BM_Evento_jogador_mouse_mover(int, int);
void BM_Evento_jogador(ALLEGRO_EVENT, void *);

/**
 * @brief 
 * - Registrar eventos de jogador
 */
void BM_Evento_Jogador_registrar()
{
    BM_Eventos_adicionar_funcao(BM_Evento_jogador, NULL);
}

/**
 * @brief 
 * - Eventos disparados pelo jogador
 */
void BM_Evento_jogador(ALLEGRO_EVENT event, void *_parametro)
{
    switch (event.type)
    {

    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        return BM_Evento_jogador_mouse_mover(event.mouse.x, event.mouse.y);

    case ALLEGRO_EVENT_KEY_DOWN:

        switch (event.keyboard.keycode)
        {
        case ALLEGRO_KEY_A:
            return BM_Evento_jogador_atacar();

        case ALLEGRO_KEY_S:
            return BM_Evento_jogador_conquistar();

        case ALLEGRO_KEY_T:
            return BM_Evento_jogador_reiniciar();
        }
    }
}

/**
 * @brief 
 * - Iniciar operações de ataque o jogador
 */
void BM_Evento_jogador_atacar()
{
    if (BM_Campo_getCampo()->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado == JOGADOR)
    {
        if (BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_ALVO) > 0)
        {
            BM_Hexagono_marcar_sincronia(JOGADOR);
            BM_Eventos_Funcoes_remover(BM_Evento_jogador);
            BM_Evento_Jogador_alvo_registrar();
            BM_Communication_Send_toggle_sincronia(1);
        }
    }
}

/**
 * @brief 
 * - Iniciar operações de conquista de territorio do jogador
 */
void BM_Evento_jogador_conquistar()
{
    if (BM_Campo_getCampo()->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado != ADVERSARIO)
    {
        BM_Elemento_adicionar_mouse_listener();
        BM_Eventos_Funcoes_remover(BM_Evento_jogador);
        BM_Evento_Jogador_Escolha_registrar();
        BM_Render_adicionar_funcao(BM_Render_elementos, NULL);
    }
}

/**
 * @brief 
 * - Reiniciar jogo
 */
void BM_Evento_jogador_reiniciar()
{
    BM_Eventos_Funcoes_remover(BM_Evento_jogador);
    BM_Render_remover_funcao(BM_Render_rodada);
}

/**
 * @brief 
 * - Mover jogador para a posição informada
 */
void BM_Evento_jogador_mouse_mover(int x, int y)
{
    BM_HEXAGONO *hexagon = BM_Player_mover(BM_Player_getJogador(), x, y);
    if (hexagon != NULL)
        BM_Communication_Send_move_player(hexagon->id);
}