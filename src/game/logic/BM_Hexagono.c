#include <stdarg.h>
#include "BM_Campo.h"
#include "BM_Player.h"
#include "bm_allegro.h"
#include "bm_display.h"
#include "BM_Hexagono.h"
#include "BM_Recursos.h"
#include "BM_Elemento.h"
#include "BM_Oponente.h"
#include "BM_Recursos_Animacao.h"
#include "bm_allegro_mouse_callback_queue.h"

static const int BM_Sincronia[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 1, -2, 2, -1, -1, 1},
    {0, -2, 1, -1, 2, 1, -1},
    {0, 2, -1, 1, -2, -1, 1},
    {0, -1, 2, -2, 1, 1, -1},
    {0, 1, 2, -1, -1, 1, -2},
    {0, 1, -1, 2, -1, -2, 1}};

static const int BM_Vantagem[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0}};

void BM_Hexagono_adicionar_listener_mouse(BM_HEXAGONO *_alvo, int _acao);
void BM_Hexagono_adicionar_animacao(BM_HEXAGONO *_alvo);

BM_HEXAGONO BM_Hexagono_criar(int _id, int _estado, int _elemento)
{
  BM_HEXAGONO temp = {_id, _estado, _elemento, 0, HEXAGONO_NORMAL};
  return temp;
}

void BM_Hexagono_alterar(int _hexagono_id, int _estado, int _elemento)
{
  BM_Campo *campo = bm_field_get();
  campo->hexagonos[_hexagono_id].estado = _estado;
  campo->hexagonos[_hexagono_id].elemento = _elemento;
}

int BM_Hexagono_batalha(int _alvo, int _atacante, int _playerAtaque, int _playerDefesa)
{
  int resultadoAtaque = 0, resultadoDefesa = 0;
  BM_Campo *campo = bm_field_get();
  BM_HEXAGONO *hexagonoAtaque, *hexagonoDefesa;

  hexagonoAtaque = &campo->hexagonos[_atacante];
  hexagonoDefesa = &campo->hexagonos[_alvo];

  BM_Hexagono_adicionar_animacao(hexagonoAtaque);
  BM_Hexagono_adicionar_animacao(hexagonoDefesa);

  hexagonoAtaque->visivel = 1;
  hexagonoDefesa->visivel = 1;

  if (BM_Vantagem[hexagonoAtaque->elemento][hexagonoDefesa->elemento] == 1)
  {
    resultadoAtaque += 4;
  }
  else if (BM_Vantagem[hexagonoDefesa->elemento][hexagonoAtaque->elemento] == 1)
  {
    resultadoDefesa += 4;
  }

  resultadoAtaque += BM_Hexagono_calcular_sincronia(*hexagonoAtaque, _playerAtaque);
  resultadoDefesa += BM_Hexagono_calcular_sincronia(*hexagonoDefesa, _playerDefesa);

  if ((hexagonoAtaque->elemento != 0 && hexagonoDefesa->elemento == 0) || (resultadoAtaque > resultadoDefesa))
  {
    return VITORIA_ATAQUE;
  }
  if ((hexagonoDefesa->elemento != 0 && hexagonoAtaque->elemento == 0) || (resultadoDefesa > resultadoAtaque))
  {
    return VITORIA_DEFESA;
  }

  return EMPATE;
}

int BM_Hexagono_marcar_alvos(int _centro, int _acao)
{
  BM_Campo *campo = bm_field_get();
  BM_HEXAGONO hexagono = campo->hexagonos[_centro], *aux;
  int i, contador = 0;
  for (i = 0; i < 6; i++)
  {
    if (hexagono.conexoes[i] != -1)
    {
      aux = &campo->hexagonos[hexagono.conexoes[i]];
      if (aux->estado == ADVERSARIO)
      {
        BM_Hexagono_adicionar_listener_mouse(aux, _acao);
        aux->alvo = _acao;
        contador++;
      }
    }
  }
  return contador;
}

void BM_Hexagono_marcar_sincronia(int _player)
{
  int i;
  BM_Campo *campo = bm_field_get();
  BM_HEXAGONO hexagono, *aux;

  hexagono = _player == JOGADOR
                 ? campo->hexagonos[BM_Player_getJogador()->hexagonoAtual]
                 : campo->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual];

  for (i = 0; i < 6; i++)
  {
    if (hexagono.conexoes[i] != -1)
    {
      aux = &campo->hexagonos[hexagono.conexoes[i]];
      if (aux->estado == _player)
      {
        switch (BM_Sincronia[hexagono.elemento][aux->elemento])
        {
        case 2:
          aux->alvo = HEXAGONO_SINCRONIA;
          break;
        case 1:
          aux->alvo = HEXAGONO_BAIXA_SINCRONIA;
          break;
        case -1:
          aux->alvo = HEXAGONO_BAIXA_ANTI_SINCRONIA;
          break;
        case -2:
          aux->alvo = HEXAGONO_ANTI_SINCRONIA;
          break;
        }
      }
    }
  }
}

void BM_Hexagono_desmarcar_sincronia(int _player)
{
  int i;
  BM_Campo *campo = bm_field_get();
  BM_HEXAGONO hexagono, *aux;
  hexagono = _player == JOGADOR
                 ? campo->hexagonos[BM_Player_getJogador()->hexagonoAtual]
                 : campo->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual];
  for (i = 0; i < 6; i++)
  {
    if (hexagono.conexoes[i] != -1)
    {
      aux = &campo->hexagonos[hexagono.conexoes[i]];
      if (aux->estado == _player)
      {
        aux->alvo = HEXAGONO_NORMAL;
      }
    }
  }
}

void BM_Hexagono_adicionar_listener_mouse(BM_HEXAGONO *_alvo, int _acao)
{
  int finalX, finalY, *id;
  finalX = _alvo->posicaoX + SPRITES(BM_IMG_HEXAGONO_ALVO)->ajusteW;
  finalY = _alvo->posicaoY + SPRITES(BM_IMG_HEXAGONO_ALVO)->ajusteH;
  switch (_acao)
  {
  case HEXAGONO_ALVO:
    id = (int *)malloc(1 * sizeof(int));
    *id = _alvo->id;
    bm_al_mouse_callback_queue_add(NULL, _alvo->posicaoX, _alvo->posicaoY, finalX, finalY, id);
    break;
  case HEXAGONO_NORMAL:
    bm_al_mouse_callback_queue_remove(_alvo->posicaoX, _alvo->posicaoY, finalX, finalY);
    break;
  }
}

int BM_Hexagono_calcular_sincronia(BM_HEXAGONO _alvo, int _player)
{
  int resultado = 0, i;
  BM_Campo *campo = bm_field_get();
  BM_HEXAGONO aux;
  for (i = 0; i < 6; i++)
  {
    if (_alvo.conexoes[i] != -1)
    {
      aux = campo->hexagonos[_alvo.conexoes[i]];
      if (aux.estado == _player)
      {
        resultado += BM_Sincronia[_alvo.elemento][aux.elemento];
      }
    }
  }
  return resultado;
}

void BM_Hexagono_adicionar_animacao(BM_HEXAGONO *_alvo)
{
  switch (_alvo->elemento)
  {
  case LUZ:
    BM_Animacao_adicionar(SPRITES(BM_ANI_LUZ), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_FIX_YH(20)), 0.5);
    break;
  case TREVAS:
    BM_Animacao_adicionar(SPRITES(BM_ANI_TREVAS), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_FIX_YH(20)), 0.5);
    break;
  case FOGO:
    BM_Animacao_adicionar(SPRITES(BM_ANI_FOGO), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_FIX_YH(20)), 0.5);
    break;
  case AGUA:
    BM_Animacao_adicionar(SPRITES(BM_ANI_AGUA), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_FIX_YH(20)), 0.5);
    break;
  case TERRA:
    BM_Animacao_adicionar(SPRITES(BM_ANI_TERRA), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_FIX_YH(20)), 0.5);
    break;
  case AR:
    BM_Animacao_adicionar(SPRITES(BM_ANI_AR), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_FIX_YH(20)), 0.5);
  }
}

BM_HEXAGONO *BM_Hexagono_click(int _mouseX, int _mouseY)
{
  BM_Campo *campo = bm_field_get();
  BM_HEXAGONO *hexagono = NULL;
  int i, width, height;
  for (i = 0; i < campo->quantidade; i++)
  {
    hexagono = &campo->hexagonos[i];
    width = BM_FIX_XW(hexagono->posicaoX) + SPRITES(BM_IMG_HEXAGONO)->ajusteW;
    height = BM_FIX_YH(hexagono->posicaoY) + SPRITES(BM_IMG_HEXAGONO)->ajusteH;
    if (_mouseX >= BM_FIX_XW(hexagono->posicaoX) && _mouseX <= width &&
        _mouseY >= BM_FIX_YH(hexagono->posicaoY) && _mouseY <= height)
    {
      break;
    }
  }
  return i != campo->quantidade ? hexagono : NULL;
}