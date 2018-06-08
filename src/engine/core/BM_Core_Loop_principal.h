#ifndef _BM_MAIN_
#define _BM_MAIN_

#include "BM_Campo.h"
#include "BM_Allegro.h"

//==========================================================================
// Constantes
//==========================================================================
#define FPS 30

//==========================================================================
// Loop principal do jogo
//==========================================================================
void BM_Loop();

/**
 * @brief 
 * - Função que é chamada quando a engine terminar o carregamento 
 */
void BM_Core_Evento_inicial();


#endif