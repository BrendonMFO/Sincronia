#ifndef __BM_SOCKET__
#define __BM_SOCKET__

#include "BM_Socket_structs.h"

void BM_Socket_connect();

void BM_Socket_send(player_message_t *msg);

void BM_Socket_receive();

#endif