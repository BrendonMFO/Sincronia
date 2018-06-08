#ifndef __BM_SOCKET_STRUCTS__
#define __BM_SOCKET_STRUCTS__

/**
 * @brief 
 * - Estrutura de dados que o servidor recebe quando um novo
 *   jogador se conecta
 */
typedef struct s_player_connection
{
    char name[20];
} player_connection_t;

/**
 * @brief 
 * -
 */
typedef struct s_player_connection_accept
{
    long long id;
} player_connection_accept_t;

/**
 * @brief 
 * -
 */
typedef struct s_player_request_match
{
    long long id;
} player_request_match_t;

/**
 * @brief 
 * -
 */
typedef struct s_player_request_match_response
{
    int created;
    int player_pos;
    long long match_id;
    int opponent_socket;
} player_request_match_response_t;

/**
 * @brief 
 * 
 */
typedef struct s_player_request_move
{
    int hexagon;
    int opponent_socket;
} player_request_move_t;

/**
 * @brief 
 * -
 */
typedef struct s_player_capture_hexagon
{
    int hexagon;
    int element;
    int opponent_socket;
} player_capture_hexagon_t;

/**
 * @brief 
 * -
 */
typedef struct s_player_toggle_sincronia
{
    int active;
    int opponent_socket;
} player_toggle_sincronia_t;

/**
 * @brief 
 * -
 */
typedef struct s_player_request_battle
{
    int target_hexagon;
    int opponent_socket;
} player_request_battle_t;

/**
 * @brief 
 * - Estrutura de dados que possui os dados de comuniçãção entre
 *   um jogador e o servidor
 */
typedef struct s_player_message
{
    int type;
    int socket;
    union u_content {
        player_connection_t player_connection;
        player_request_move_t player_request_move;
        player_request_match_t player_request_match;
        player_request_battle_t player_request_battle;
        player_capture_hexagon_t player_capture_hexagon;
        player_toggle_sincronia_t player_toggle_sincronia;
        player_connection_accept_t player_connection_accept;
        player_request_match_response_t player_request_match_response;
    } content;
} player_message_t;

#endif