#include "BM_Campo.h"
#include "BM_Player.h"
#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Rodadas.h"
#include "BM_Oponente.h"
#include "BM_Hexagono.h"
#include "BM_Socket_events.h"
#include "BM_Communication.h"
#include "BM_Communication_Receive.h"

/**
 * @brief 
 * - Função disparada quando o servidor aceita a requisição de conexão do jogador
 */
void BM_Communication_Receive_accept(player_message_t *server_response)
{
    BM_Player_setId(server_response->content.player_connection_accept.id);
    BM_Socket_events_pop(PLAYER_CONNECT_ACCEPT, BM_Communication_Receive_accept);
}

/**
 * @brief 
 * - Função disparada quando o oponente move seu player
 */
void BM_Communication_Receive_opponent_move(player_message_t *server_response)
{
    BM_Oponente_set_hexagon(server_response->content.player_request_move.hexagon);
}

/**
 * @brief 
 * - Função disparada quando o oponente captura um dos campos disponiveis
 */
void BM_Communication_Receive_opponent_capture(player_message_t *server_response)
{
    BM_Oponente_capture_hexagon(server_response->content.player_capture_hexagon.hexagon, server_response->content.player_capture_hexagon.element);
    BM_Evento_Jogador_registrar();
    BM_Rodada_avancar();
}

/**
 * @brief 
 * - Função disparada quando o oponente ativa ou desativa a visualização de sincronia
 *   entre os elementos
 */
void BM_Communication_Receive_toggle_sincronia(player_message_t *server_response)
{
    if (server_response->content.player_toggle_sincronia.active)
        BM_Hexagono_marcar_sincronia(ADVERSARIO);
    else
        BM_Hexagono_desmarcar_sincronia(ADVERSARIO);
}

/**
 * @brief 
 * - Função disparada quando o oponente inicia uma batalha
 */
void BM_Communication_Receive_request_battle(player_message_t *server_response)
{
    BM_Oponente_executar_ataque(server_response->content.player_request_battle.target_hexagon);
    BM_Hexagono_desmarcar_sincronia(ADVERSARIO);
    BM_Evento_Jogador_registrar();
}

/**
 * @brief 
 * - Função disparada quando o servidor informa que uma partida foi encontrada ou quando o 
 *   jogador entrou na fila de espera por um adversario
 */
void BM_Communication_Receive_match_request(player_message_t *server_response)
{
    player_request_match_response_t response = server_response->content.player_request_match_response;

    if (response.created == 1)
    {
        BM_Eventos_Jogo_registrar();
        BM_Campo_inicial(response.player_pos);
        BM_Oponente_set_socket(response.opponent_socket);
        BM_Render_remover_funcao(BM_Render_esperando_oponente);
        BM_Player_iniciar_valores(response.player_pos == 1 ? 11 : 18);
        BM_Oponente_iniciar_valores(response.player_pos == 2 ? 11 : 18);

        BM_Socket_events_push(PLAYER_OPPONENT_MOVE, BM_Communication_Receive_opponent_move);
        BM_Socket_events_push(PLAYER_OPPONENT_REQUEST_BATTLE, BM_Communication_Receive_request_battle);
        BM_Socket_events_push(PLAYER_OPPONENT_CAPTURE_HEXAGON, BM_Communication_Receive_opponent_capture);
        BM_Socket_events_push(PLAYER_OPPONENT_TOGGLE_SINCRONIA, BM_Communication_Receive_toggle_sincronia);

        if (response.player_pos == 1)
            BM_Evento_Jogador_registrar();

        BM_Socket_events_pop(PLAYER_MATCH_RESPONSE, BM_Communication_Receive_match_request);
    }
}