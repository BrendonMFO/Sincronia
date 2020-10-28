#include <stdlib.h>
#include <string.h>
#include "BM_Oponente.h"
#include "BM_Socket_events.h"
#include "BM_Communication.h"
#include "BM_Communication_Send.h"
#include "BM_Communication_Receive.h"

void BM_Communication_Send_connection(char *name)
{
  player_message_t request;
  request.type = PLAYER_CONNECT;
  strncpy(request.content.player_connection.name, name, sizeof(char) * 20);
  BM_Socket_events_push(PLAYER_CONNECT_ACCEPT, BM_Communication_Receive_accept);
  BM_Socket_send(&request);
}

void BM_Communication_Send_match_request(long long player_id)
{
  player_message_t request;
  request.type = PLAYER_MATCH_REQUEST;
  request.content.player_request_match.id = player_id;
  BM_Socket_events_push(PLAYER_MATCH_RESPONSE, BM_Communication_Receive_match_request);
  BM_Socket_send(&request);
}

void BM_Communication_Send_move_player(int hexagon)
{
  player_message_t request;
  request.type = PLAYER_MOVE;
  request.content.player_request_move.hexagon = hexagon;
  request.content.player_request_move.opponent_socket = BM_Oponente_get_socket();
  BM_Socket_send(&request);
}

void BM_Communication_Send_capture_hexagon(int hexagon, int element)
{
  player_message_t request;
  request.type = PLAYER_CAPTURE_HEXAGON;
  request.content.player_capture_hexagon.hexagon = hexagon;
  request.content.player_capture_hexagon.element = element;
  request.content.player_capture_hexagon.opponent_socket = BM_Oponente_get_socket();
  BM_Socket_send(&request);
}

void BM_Communication_Send_toggle_sincronia(int active)
{
  player_message_t request;
  request.type = PLAYER_TOGGLE_SINCRONIA;
  request.content.player_toggle_sincronia.active = active;
  request.content.player_toggle_sincronia.opponent_socket = BM_Oponente_get_socket();
  BM_Socket_send(&request);
}

void BM_Communication_Send_battle(int target_hexagon)
{
  player_message_t request;
  request.type = PLAYER_REQUEST_BATTLE;
  request.content.player_request_battle.target_hexagon = target_hexagon;
  request.content.player_request_battle.opponent_socket = BM_Oponente_get_socket();
  BM_Socket_send(&request);
}