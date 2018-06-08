//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#ifndef __BM_COMMUNICATION_RECEIVE__
#define __BM_COMMUNICATION_RECEIVE__

#include "BM_Socket.h"

/**
 * @brief 
 * - Função disparada quando o servidor aceita a requisição de conexão do jogador
 */
void BM_Communication_Receive_accept(player_message_t *server_response);

/**
 * @brief 
 * - Função disparada quando o oponente move seu player
 */
void BM_Communication_Receive_opponent_move(player_message_t *server_response);

/**
 * @brief 
 * - Função disparada quando o oponente captura um dos campos disponiveis
 */
void BM_Communication_Receive_opponent_capture(player_message_t *server_response);

/**
 * @brief 
 * - Função disparada quando o oponente ativa ou desativa a visualização de sincronia
 *   entre os elementos
 */
void BM_Communication_Receive_toggle_sincronia(player_message_t *server_response);

/**
 * @brief 
 * - Função disparada quando o oponente inicia uma batalha
 */
void BM_Communication_Receive_request_battle(player_message_t *server_response);

/**
 * @brief 
 * - Função disparada quando o servidor informa que uma partida foi encontrada ou quando o 
 *   jogador entrou na fila de espera por um adversario
 */
void BM_Communication_Receive_match_request(player_message_t *server_response);

#endif