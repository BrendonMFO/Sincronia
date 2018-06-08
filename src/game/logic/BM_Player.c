//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Player.h"
#include "BM_Allegro_eventos.h"
#include "BM_Allegro_eventos_funcoes.h"
#include "BM_Allegro_janela.h"
#include "BM_Campo.h"
#include "BM_Recursos.h"
#include <stdio.h>
#include <stdlib.h>

//==========================================================================
// Variaveis
//==========================================================================
static BM_PLAYER *jogador = NULL;
static long long jogador_id = 0;

//==========================================================================
// Prototipos
//==========================================================================
void BM_Player_elementos();

//==========================================================================
// Iniciar player
//==========================================================================
int BM_Player_iniciar(int _hexagonoInicialJogador)
{
	jogador = (BM_PLAYER *)malloc(1 * sizeof(BM_PLAYER));
	if (jogador == NULL)
	{
		fprintf(stderr, "Erro: Nao foi possivel alocar memoria para um player");
		exit(-1);
	}
	BM_Player_iniciar_valores(_hexagonoInicialJogador);

	return 1;
}

//==========================================================================
// Get jogador
//==========================================================================
BM_PLAYER *BM_Player_getJogador()
{
	return jogador;
}

//==========================================================================
/**
 * @brief 
 */
//==========================================================================
long long BM_Player_getId()
{
	return jogador_id;
}

//==========================================================================
/**
 * @brief 
 */
//==========================================================================
void BM_Player_setId(long long id)
{
	jogador_id = id;
}

//==========================================================================
// Iniciar valores da estrutura de jogadores
//==========================================================================
void BM_Player_iniciar_valores(int _hexagono)
{
	jogador->hexagonoAtual = _hexagono;
	jogador->quantidadeTerritorio = 5;
	jogador->elementosDisponivel.luz = 1;
	jogador->elementosDisponivel.trevas = 1;
	jogador->elementosDisponivel.fogo = 1;
	jogador->elementosDisponivel.agua = 1;
	jogador->elementosDisponivel.terra = 1;
	jogador->elementosDisponivel.ar = 1;
	jogador->elementosTempo.luz = 0;
	jogador->elementosTempo.trevas = 0;
	jogador->elementosTempo.fogo = 0;
	jogador->elementosTempo.agua = 0;
	jogador->elementosTempo.terra = 0;
	jogador->elementosTempo.ar = 0;
	BM_Campo_getCampo()->hexagonos[_hexagono].estado = JOGADOR;
}

//==========================================================================
// Checar se o elemento esta disponivel
//==========================================================================
int BM_Player_disponibilidade_elemento(int _elemento)
{
	int *elemento = &jogador->elementosDisponivel.luz;
	return elemento[_elemento - 1];
}

//==========================================================================
// Checar elemento
//==========================================================================
void BM_Player_checar_elemento(int _elemento)
{
	int *elemento = &jogador->elementosDisponivel.luz;
	elemento[_elemento - 1] = 0;
	BM_Player_elementos();
}

//==========================================================================
// Liberar elementos se todos já tiverem sido usados
//==========================================================================
void BM_Player_elementos()
{
	int i, *elemento, vazio = 1;
	elemento = &jogador->elementosDisponivel.luz;
	for (i = 0; i < 6; i++, elemento++)
	{
		if (*elemento == 1)
			vazio = 0;
	}
	if (vazio == 1)
	{
		elemento = &jogador->elementosDisponivel.luz;
		for (i = 0; i < 6; i++, elemento++)
		{
			*elemento = 1;
		}
	}
}

//==========================================================================
// Checar tempo elemento
//==========================================================================
void BM_Player_checar_tempo()
{
	int *elementoTempo, *elemento, i;
	elementoTempo = &jogador->elementosTempo.luz;
	for (i = 0; i < 6; i++, elementoTempo++)
	{
		(*elementoTempo)++;
	}
	elementoTempo = &jogador->elementosTempo.luz;
	elemento = &jogador->elementosDisponivel.luz;
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
// Alterar hexagono que o player esta atualmente
//==========================================================================
BM_HEXAGONO *BM_Player_mover(BM_PLAYER *_player, int _mouseX, int _mouseY)
{
	BM_Campo *campo = BM_Campo_getCampo();
	BM_HEXAGONO *hexagono = NULL, *aux = NULL;
	int i, j, pos, largura, altura;
	for (i = 0; i < campo->quantidade; i++)
	{
		hexagono = &campo->hexagonos[i];
		largura = BM_AJUSTE_XW(hexagono->posicaoX) + SPRITES(BM_IMG_HEXAGONO)->ajusteW;
		altura = BM_AJUSTE_YH(hexagono->posicaoY) + SPRITES(BM_IMG_HEXAGONO)->ajusteH;
		if (_mouseX >= BM_AJUSTE_XW(hexagono->posicaoX) && _mouseX <= largura &&
			_mouseY >= BM_AJUSTE_YH(hexagono->posicaoY) && _mouseY <= altura)
		{
			break;
		}
	}
	if (i >= campo->quantidade || i == _player->hexagonoAtual || hexagono->estado == ADVERSARIO)
		return NULL;
	if (hexagono->estado == JOGADOR)
	{
		_player->hexagonoAtual = hexagono->id;
	}
	else
	{
		for (j = 0; j < 6; j++)
		{
			pos = hexagono->conexoes[j];
			if (pos != -1)
			{
				aux = &campo->hexagonos[pos];
				if (aux->estado == JOGADOR)
				{
					_player->hexagonoAtual = hexagono->id;
					break;
				}
			}
		}
	}
	return hexagono;
}
