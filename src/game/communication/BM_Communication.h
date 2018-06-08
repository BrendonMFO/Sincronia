//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#ifndef __BM_COMMUNICATION__
#define __BM_COMMUNICATION__

/**
 * @brief 
 */
enum COMMUNICATION_SEND
{
    PLAYER_CONNECT = 1,
    PLAYER_MATCH_REQUEST = 3,
    PLAYER_MOVE = 5,
    PLAYER_CAPTURE_HEXAGON = 7,
    PLAYER_TOGGLE_SINCRONIA = 9,
    PLAYER_REQUEST_BATTLE = 11
};

/**
 * @brief 
 */
enum COMMUNICATION_RECEIVE
{
    PLAYER_CONNECT_ACCEPT = 2,
    PLAYER_MATCH_RESPONSE = 4,
    PLAYER_OPPONENT_MOVE = 6,
    PLAYER_OPPONENT_CAPTURE_HEXAGON = 8,
    PLAYER_OPPONENT_TOGGLE_SINCRONIA = 10,
    PLAYER_OPPONENT_REQUEST_BATTLE = 12
};

#endif