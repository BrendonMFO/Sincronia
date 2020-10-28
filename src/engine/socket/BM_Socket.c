#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "BM_Socket.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "BM_Socket_events.h"

#ifndef PORT
#define PORT 4080
#endif

#ifndef IP_SERVER
#define IP_SERVER "127.0.0.1"
#endif

static int sock;
static struct sockaddr_in serv_addr;

void BM_Socket_init();

void BM_Socket_connect()
{
  BM_Socket_init();
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Connection Failed \n");
    exit(EXIT_FAILURE);
  }
}

void BM_Socket_send(player_message_t *msg)
{
  send(sock, msg, sizeof(player_message_t), 0);
}

void BM_Socket_receive()
{
  player_message_t *msg = (player_message_t *)malloc(sizeof(player_message_t));
  read(sock, msg, sizeof(player_message_t));
  BM_Socket_events_call(msg->type, msg);
}

void BM_Socket_init()
{
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("Socket creation error\n");
    exit(EXIT_FAILURE);
  }

  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, IP_SERVER, &serv_addr.sin_addr) <= 0)
  {
    printf("Invalid address/ Address not supported\n");
    exit(EXIT_FAILURE);
  }
}
