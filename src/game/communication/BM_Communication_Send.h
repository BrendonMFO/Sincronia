#ifndef __BM_COMMUNICATION_SEND__
#define __BM_COMMUNICATION_SEND__

#include "BM_Socket_structs.h"

/**
 * @brief 
 * 
 * @param name 
 */
void BM_Communication_Send_connection(char *name);

/**
 * @brief 
 * -
 */
void BM_Communication_Send_match_request(long long player_id);

/**
 * @brief 
 * -
 */
void BM_Communication_Send_move_player(int hexagon);

/**
 * @brief 
 * -
 */
void BM_Communication_Send_capture_hexagon(int hexagon, int element);

/**
 * @brief 
 * -
 */
void BM_Communication_Send_toggle_sincronia(int active);

/**
 * @brief 
 * -
 */
void BM_Communication_Send_battle(int target_hexagon);

#endif