#ifndef _BM_LOGIC_CAMPO_
#define _BM_LOGIC_CAMPO_

#include <stdio.h>
#include <string.h>
#include "BM_Hexagono.h"

//==========================================================================
// Estrutura de dados do campo
//==========================================================================
typedef struct BM_Campo_S
{
	int quantidade;
	BM_HEXAGONO *hexagonos;
} BM_Campo;

//==========================================================================
// Criar campo apartir de um arquivo
//==========================================================================
BM_Campo *BM_Campo_getCampo();

//==========================================================================
// Setar arquivo de campo
//==========================================================================
void BM_Campo_setCampo(char *_campo);

//==========================================================================
// Redefinir campo
//==========================================================================
void BM_Campo_redefinir();

#endif