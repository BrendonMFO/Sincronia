//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#ifndef __BM_SOCKET__
#define __BM_SOCKET__

#include "BM_Socket_structs.h"

/**
 * @brief 
 * - Função responsavel por iniciar a comunicação com o servidor
 */
void BM_Socket_connect();

/**
 * @brief 
 * - Função responsavel por enviar dados para o servidor
 * 
 * @param msg 
 * - Mensagem que será enviada
 */
void BM_Socket_send(player_message_t *msg);

/**
 * @brief 
 * - Função responsavel por receber dados enviados pelo servidor
 */
void BM_Socket_receive();

#endif