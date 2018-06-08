//======================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//======================================================================

#ifndef _BM_RENDERS_
#define _BM_RENDERS_

#include "BM_Core_Renders.h"

/**
 * @brief 
 * - Iniciar renderização de todos os hexagonos
 */
void BM_Render_campo();

/**
 * @brief 
 * - Função responsavel por renderizar a imagem de background do cenario
 */
void BM_Render_campo_background();

/**
 * @brief 
 * - Função responsavel por renderizar todas as animações que estão
 *   pendentes na fila de animações
 */
void BM_Render_animacao();

/**
 * @brief 
 * - Iniciar renderização de todos os hexagonos
 */
void BM_Render_campo();

/**
 * @brief 
 * - Renderizar tutorial
 */
void BM_Render_tutorial();

/**
 * @brief 
 * - Renderizar tela de aguargando oponente
 */
void BM_Render_esperando_oponente();

/**
 * @brief 
 * - Renderizar elementos
 */
void BM_Render_elementos();

/**
 * @brief 
 * - Renderizar Rodadas
 */
void BM_Render_rodada();

/**
 * @brief 
 * - Renderizar resultado
 */
void BM_Render_resultado();

/**
 * @brief 
 * - Renderizar player do jogador principal
 */
void BM_Render_player();

/**
 * @brief 
 * - Renderizar player adversario
 */
void BM_Render_player_ia();

#endif