#ifndef __BM_SOCKET_EVENTS__
#define __BM_SOCKET_EVENTS__

#include "BM_Socket.h"

/**
 * @brief 
 */
typedef struct s_communication_callback
{
    struct s_communication_callback *prev;
    int type;
    void (*funcao)(player_message_t *);
    struct s_communication_callback *next;
} communication_callback_t;

/**
 * @brief 
 */
typedef struct s_communication_callback_list
{
    communication_callback_t *first;
    communication_callback_t *last;
} communication_callback_list_t;

/**
 * @brief 
 * 
 */
void BM_Socket_events_init();

/**
 * @brief 
 * 
 * @param type 
 * @param funcao 
 */
void BM_Socket_events_push(int type, void (*funcao)(player_message_t *));

/**
 * @brief 
 * 
 */
void BM_Socket_events_pop(int type, void (*funcao)(player_message_t *));

/**
 * @brief 
 * 
 * @param type 
 * @param message 
 */
void BM_Socket_events_call(int type, player_message_t *message);

#endif