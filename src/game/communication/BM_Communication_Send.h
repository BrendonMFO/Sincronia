#ifndef __BM_COMMUNICATION_SEND__
#define __BM_COMMUNICATION_SEND__

#include "bm_socket_structs.h"

void BM_Communication_Send_connection(char *name);

void BM_Communication_Send_match_request(long long player_id);

void BM_Communication_Send_move_player(int hexagon);

void BM_Communication_Send_capture_hexagon(int hexagon, int element);

void BM_Communication_Send_toggle_sincronia(int active);

void BM_Communication_Send_battle(int target_hexagon);

#endif