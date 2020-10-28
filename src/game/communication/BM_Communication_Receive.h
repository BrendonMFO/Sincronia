#ifndef __BM_COMMUNICATION_RECEIVE__
#define __BM_COMMUNICATION_RECEIVE__

#include "BM_Socket.h"

void BM_Communication_Receive_accept(player_message_t *server_response);

void BM_Communication_Receive_opponent_move(player_message_t *server_response);

void BM_Communication_Receive_opponent_capture(player_message_t *server_response);

void BM_Communication_Receive_toggle_sincronia(player_message_t *server_response);

void BM_Communication_Receive_request_battle(player_message_t *server_response);

void BM_Communication_Receive_match_request(player_message_t *server_response);

#endif