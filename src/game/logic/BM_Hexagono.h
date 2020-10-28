#ifndef _BM_LOGIC_HEXAGONO_
#define _BM_LOGIC_HEXAGONO_

#define VITORIA_ATAQUE 1
#define VITORIA_DEFESA 2
#define EMPATE 3

enum BM_HEXAGONO_ESTADO
{
  NEUTRO = 0,
  JOGADOR,
  ADVERSARIO
};

enum BM_HEXAGONO_SINCRONIA
{
  HEXAGONO_NORMAL,
  HEXAGONO_ALVO,
  HEXAGONO_SINCRONIA,
  HEXAGONO_ANTI_SINCRONIA,
  HEXAGONO_BAIXA_ANTI_SINCRONIA,
  HEXAGONO_BAIXA_SINCRONIA
};

typedef struct BM_HEXAGONO_S
{
  int id;
  int estado;
  int elemento;
  int visivel;
  int alvo;
  int posicaoX;
  int posicaoY;
  int conexoes[6];
} BM_HEXAGONO;

BM_HEXAGONO BM_Hexagono_criar(int _id, int _estado, int _elemento);

void BM_Hexagono_alterar(int _hexagono_id, int _estado, int _elemento);

int BM_Hexagono_marcar_alvos(int _centro, int _acao);

int BM_Hexagono_batalha(int _alvo, int _atacante, int _playerAtaque, int _playerDefesa);

int BM_Hexagono_calcular_sincronia(BM_HEXAGONO _alvo, int _player);

void BM_Hexagono_marcar_sincronia(int _player);

void BM_Hexagono_desmarcar_sincronia(int _player);

BM_HEXAGONO *BM_Hexagono_click(int _mouseX, int _mouseY);

#endif