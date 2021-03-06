#ifndef __BM_SOCKET_EVENTS__
#define __BM_SOCKET_EVENTS__

#include "bm_socket.h"

typedef struct s_communication_callback
{
  struct s_communication_callback *prev;
  int type;
  void (*callback)(player_message_t *);
  struct s_communication_callback *next;
} communication_callback_t;

typedef struct s_communication_callback_list
{
  communication_callback_t *first;
  communication_callback_t *last;
} communication_callback_list_t;

void bm_socket_events_init();

void bm_socket_events_push(int type, void (*callback)(player_message_t *));

void bm_socket_events_pop(int type, void (*callback)(player_message_t *));

void bm_socket_events_call(int type, player_message_t *message);

#endif