//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#ifndef _BM_EVENTOS_
#define _BM_EVENTOS_

#include "BM_Core_Renders.h"
#include "BM_Allegro_eventos_funcoes.h"

/**
 * @brief 
 * - Iniciar jogo
 */
void BM_Eventos_Jogo_registrar();

/**
 * @brief 
 * - Função que será executada sempre que o EVENTO JOGADOR
 *   for chamado 
 */
void BM_Evento_Jogador_alvo_registrar();

/**
 * @brief 
 * - Registrar eventos de jogador
 */
void BM_Evento_Jogador_registrar();

/**
 * @brief 
 * - Adicionar eventos na lista de funções e renderizações relacionados aos
 *   tutoriais
 */
void BM_Eventos_Tutorial_registrar();

/**
 * @brief 
 * - Registrar eventos de escolha
 */
void BM_Evento_Jogador_Escolha_registrar();

/**
 * @brief 
 * - Função responsavel por iniciar o procedimento para iniciar uma partida
 */
void BM_Eventos_Partida_procurar();

#endif