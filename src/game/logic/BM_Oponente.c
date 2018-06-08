#include <stdio.h>
#include <stdarg.h>
#include "BM_Campo.h"
#include "BM_Rodadas.h"
#include "BM_Eventos.h"
#include "BM_Hexagono.h"
#include "BM_Oponente.h"
#include "BM_Core_Eventos.h"
#include "BM_Allegro_eventos.h"

//==========================================================================
// Estrutura de ação da IA
//==========================================================================
typedef struct BM_Oponente_ACAO_S
{
	int tempoFrames;
	int tempoAtual;
} BM_Oponente_ACAO;

//==========================================================================
// Variaveis
//==========================================================================
BM_PLAYER *ia = NULL;
BM_Oponente_ACAO BM_Oponente_acao;
int BM_Oponente_socket;

//==========================================================================
// Prototipos
//==========================================================================
int BM_Oponente_checar_elemento();

//==========================================================================
// Iniciar player IA
//==========================================================================
int BM_Oponente_iniciar(int _hexagonoAtual)
{
	ia = (BM_PLAYER *)malloc(sizeof(BM_PLAYER));

	if (ia == NULL)
	{
		fprintf(stderr, "Erro: Nao foi possivel alocar memoria para um player");
		exit(-1);
	}

	BM_Oponente_iniciar_valores(_hexagonoAtual);

	return 1;
}

//==========================================================================
// Get IA
//==========================================================================
BM_PLAYER *BM_Player_getOpponentPlayer()
{
	return ia;
}

//==========================================================================
// Set socket
//==========================================================================
void BM_Oponente_set_socket(int socket)
{
	BM_Oponente_socket = socket;
}

//==========================================================================
/**
 * @brief 
 * -
 */
//==========================================================================
void BM_Oponente_capture_hexagon(int hexagon, int element)
{
	if (BM_Campo_getCampo()->hexagonos[ia->hexagonoAtual].estado != ADVERSARIO)
		ia->quantidadeTerritorio++;

	BM_Hexagono_alterar(hexagon, ADVERSARIO, element);
}

//==========================================================================
// Get socket
//==========================================================================
int BM_Oponente_get_socket()
{
	return BM_Oponente_socket;
}

//==========================================================================
/**
 * @brief 
 * - Definir a posição atual do player do oponente
 */
//==========================================================================
void BM_Oponente_set_hexagon(int hexagon)
{
	ia->hexagonoAtual = hexagon;
}

//==========================================================================
// Iniciar valores da estrutura de jogadores
//==========================================================================
void BM_Oponente_iniciar_valores(int _hexagono)
{
	ia->quantidadeTerritorio = 5;
	ia->elementosDisponivel.luz = 1;
	ia->elementosDisponivel.trevas = 1;
	ia->elementosDisponivel.fogo = 1;
	ia->elementosDisponivel.agua = 1;
	ia->elementosDisponivel.terra = 1;
	ia->elementosDisponivel.ar = 1;
	ia->elementosTempo.luz = 0;
	ia->elementosTempo.trevas = 0;
	ia->elementosTempo.fogo = 0;
	ia->elementosTempo.agua = 0;
	ia->elementosTempo.terra = 0;
	ia->elementosTempo.ar = 0;
	BM_Oponente_set_hexagon(_hexagono);
	BM_Campo_getCampo()->hexagonos[_hexagono].estado = ADVERSARIO;
}

//==========================================================================
// Checar elemento
//==========================================================================
int BM_Oponente_checar_elemento()
{
	int elementosDisponiveis = 0, ordemElementos[6], vazio = 1, *elemento, i, resultado;
	elemento = &ia->elementosDisponivel.luz;
	for (i = 0; i < 6; i++, elemento++)
	{
		if (*elemento == 1)
		{
			ordemElementos[elementosDisponiveis++] = i + 1;
			vazio = 0;
		}
	}
	if (vazio == 1)
	{
		elemento = &ia->elementosDisponivel.luz;
		for (i = 0; i < 6; i++, elemento++)
		{
			*elemento = 1;
		}
	}
	resultado = ordemElementos[rand() % elementosDisponiveis];
	elemento = &ia->elementosDisponivel.luz;
	elemento[resultado] = 0;
	return ordemElementos[rand() % elementosDisponiveis];
}

//==========================================================================
// Checar tempo elemento
//==========================================================================
void BM_Oponente_checar_tempo()
{
	int *elementoTempo, *elemento, i;
	elementoTempo = &ia->elementosTempo.luz;
	for (i = 0; i < 6; i++, elementoTempo++)
	{
		(*elementoTempo)++;
	}
	elementoTempo = &ia->elementosTempo.luz;
	elemento = &ia->elementosDisponivel.luz;
	for (i = 0; i < 6; i++, elementoTempo++, elemento++)
	{
		if (*elementoTempo == 4)
		{
			*elementoTempo = 0;
			*elemento = 1;
		}
	}
}

//==========================================================================
// Executar ataque
//==========================================================================
void BM_Oponente_executar_ataque(int _alvo)
{
	BM_Campo *campo = BM_Campo_getCampo();
	switch (BM_Hexagono_batalha(campo->hexagonos[_alvo].id, ia->hexagonoAtual, ADVERSARIO, JOGADOR))
	{
	case VITORIA_ATAQUE:
		campo->hexagonos[_alvo].estado = ADVERSARIO;
		BM_Player_getOpponentPlayer()->quantidadeTerritorio++;
		BM_Player_getJogador()->quantidadeTerritorio--;
		break;
	case VITORIA_DEFESA:
		campo->hexagonos[ia->hexagonoAtual].estado = JOGADOR;
		BM_Player_getOpponentPlayer()->quantidadeTerritorio--;
		BM_Player_getJogador()->quantidadeTerritorio++;
	}
	campo->hexagonos[_alvo].alvo = HEXAGONO_NORMAL;
	BM_Hexagono_desmarcar_sincronia(ADVERSARIO);
	BM_Rodada_avancar();
}