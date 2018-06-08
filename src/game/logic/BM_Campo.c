#include "BM_Campo.h"
#include "BM_Allegro_janela.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//==========================================================================
// Variavel que ira conter os dados do campo
//==========================================================================
BM_Campo *campo = NULL;
char *nome_campo;

//==========================================================================
// Prototipos
//==========================================================================
int numeroAleatorio(int _numero);
void carregarHexagonos(BM_HEXAGONO *_hexagonos, FILE *_arquivo, int _quantidadeLinhas);

//==========================================================================
// Criar campo apartir de um arquivo
//==========================================================================
BM_Campo *BM_Campo_getCampo()
{
	if (campo == NULL)
	{
		if (nome_campo == NULL)
		{
			fprintf(stderr, "Erro: nao ha um arquivo de campo definido\n");
			exit(-1);
		}

		campo = (BM_Campo *)malloc(1 * sizeof(BM_Campo));
		if (campo == NULL)
		{
			fprintf(stderr, "Erro: nao foi possivel alocar memoria de campo\n");
			exit(-1);
		}

		FILE *arquivo = fopen(nome_campo, "r");
		if (arquivo == NULL)
		{
			fprintf(stderr, "Erro: nao foi possivel abrir arquivo de campo\n");
			exit(-1);
		}
		fscanf(arquivo, "Grafos = %d\n", &campo->quantidade);

		campo->hexagonos = (BM_HEXAGONO *)malloc(campo->quantidade * sizeof(BM_HEXAGONO));
		if (campo->hexagonos == NULL)
		{
			fprintf(stderr, "Erro: nao foi possivel montar os hexagonos do campo\n");
			exit(-1);
		}
		carregarHexagonos(campo->hexagonos, arquivo, campo->quantidade);
	}

	return campo;
}

//==========================================================================
// Setar arquivo de campo
//==========================================================================
void BM_Campo_setCampo(char *_campo)
{
	nome_campo = (char *)malloc(strlen(_campo) * sizeof(char));
	strcpy(nome_campo, _campo);
}

//==========================================================================
// Popular vetor de hexagonos
//==========================================================================
void carregarHexagonos(BM_HEXAGONO *_hexagonos, FILE *_arquivo, int _quantidadeLinhas)
{
	int contador;
	for (contador = 0; contador < _quantidadeLinhas; contador++)
	{
		_hexagonos[contador] = BM_Hexagono_criar(contador, NEUTRO, 0);
		fscanf(_arquivo, "X : %d Y : %d Conexoes : [ %d %d %d %d %d %d ]\n",
			   &_hexagonos[contador].posicaoX,
			   &_hexagonos[contador].posicaoY,
			   &_hexagonos[contador].conexoes[0],
			   &_hexagonos[contador].conexoes[1],
			   &_hexagonos[contador].conexoes[2],
			   &_hexagonos[contador].conexoes[3],
			   &_hexagonos[contador].conexoes[4],
			   &_hexagonos[contador].conexoes[5]);
	}
	fclose(_arquivo);
}

//==========================================================================
// Sortear um elemento aleatorio
//==========================================================================
int numeroAleatorio(int _numero)
{
	return rand() % _numero;
}

//==========================================================================
// Redefinir campo
//==========================================================================
void BM_Campo_redefinir()
{
	int contador;
	for (contador = 0; contador < campo->quantidade; contador++)
	{
		campo->hexagonos[contador].estado = NEUTRO;
		campo->hexagonos[contador].elemento = 0;
	}
}

//==========================================================================
/**
 * @brief 
 * - Definir o campo inicial
 */
//==========================================================================
void BM_Campo_inicial(int player_pos)
{
	BM_Hexagono_alterar(1, player_pos == 1 ? ADVERSARIO : JOGADOR, 0);
	BM_Hexagono_alterar(2, player_pos == 2 ? ADVERSARIO : JOGADOR, 0);
	BM_Hexagono_alterar(7, player_pos == 2 ? ADVERSARIO : JOGADOR, 0);
	BM_Hexagono_alterar(9, player_pos == 1 ? ADVERSARIO : JOGADOR, 0);
	BM_Hexagono_alterar(15, player_pos == 1 ? ADVERSARIO : JOGADOR, 0);
	BM_Hexagono_alterar(16, player_pos == 2 ? ADVERSARIO : JOGADOR, 0);
	BM_Hexagono_alterar(22, player_pos == 2 ? ADVERSARIO : JOGADOR, 0);
	BM_Hexagono_alterar(23, player_pos == 1 ? ADVERSARIO : JOGADOR, 0);
}