#ifndef __BM_SOCKET__
#define __BM_SOCKET__

#include "bm_socket_structs.h"

void bm_socket_connect();

void bm_socket_send(player_message_t *msg);

void bm_socket_receive();

#endif