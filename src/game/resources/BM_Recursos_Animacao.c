#include <stdio.h>
#include <stdlib.h>
#include "bm_allegro_main_events.h"
#include "BM_Recursos_Animacao.h"

static BM_ANIMACAO_FILA *animacoes = NULL;

void BM_Animacao_processar();
BM_ANIMACAO *BM_Animacao_procurar_fila(BM_ANIMACAO *_animacao);

BM_ANIMACAO_FILA *BM_Animacao_obter_fila()
{
  return animacoes;
}

int BM_Animacao_iniciar_fila()
{
  animacoes = (BM_ANIMACAO_FILA *)malloc(1 * sizeof(BM_ANIMACAO_FILA));
  if (animacoes == NULL)
  {
    fprintf(stderr, "Erro: Nao foi possivel alocar memoria para a fila de animacoes\n");
    return 0;
  }
  animacoes->first = NULL;
  animacoes->last = NULL;
  return 1;
}

int BM_Animacao_adicionar(BM_SPRITES *_sprite, int _renderW, int _renderH, int _renderX, int _renderY, double _tempo)
{
  BM_ANIMACAO *aux = (BM_ANIMACAO *)malloc(1 * sizeof(BM_ANIMACAO));
  if (aux == NULL)
  {
    fprintf(stderr, "Erro: Nao foi possivel alocar memoria para uma animacao\n");
    return 0;
  }
  aux->sprite = _sprite;
  aux->frameAtualColuna = 0;
  aux->frameAtualLinha = 0;
  aux->destinoW = _renderW;
  aux->destinoH = _renderH;
  aux->destinoX = _renderX;
  aux->destinoY = _renderY;
  aux->finalizado = 2;
  aux->render = 2;
  aux->previous = NULL;
  aux->tempoAtualizacao = (_tempo / (aux->sprite->imagem->columns * aux->sprite->imagem->lines)) * 100;
  aux->tempoAtual = 0;
  if (animacoes->first == NULL)
  {
    animacoes->first = aux;
    animacoes->last = aux;
    aux->next = NULL;
    bm_events_add_callback(BM_Animacao_processar, NULL);
  }
  else
  {
    animacoes->first->previous = aux;
    aux->next = animacoes->first;
    animacoes->first = aux;
  }
  return 1;
}

void BM_Animacao_remover(BM_ANIMACAO *_animacao)
{
  BM_ANIMACAO *aux = BM_Animacao_procurar_fila(_animacao);
  if (aux == NULL)
  {
    return;
  }
  if (animacoes->first == animacoes->last)
  {
    animacoes->first = NULL;
    animacoes->last = NULL;
    bm_events_remove_callback(BM_Animacao_processar);
  }
  else
  {
    if (aux->previous != NULL)
    {
      aux->previous->next = aux->next;
    }
    else
    {
      animacoes->first = aux->next;
    }
    if (aux->next != NULL)
    {
      aux->next->previous = aux->previous;
    }
    else
    {
      animacoes->last = aux->previous;
    }
  }
  free(aux);
}

void BM_Animacao_avancar(BM_ANIMACAO *_animacao)
{
  if (_animacao != NULL)
  {
    _animacao->frameAtualColuna++;
    if (_animacao->frameAtualColuna > _animacao->sprite->imagem->columns - 1)
    {
      _animacao->frameAtualLinha++;
      _animacao->frameAtualColuna = 0;
      if (_animacao->frameAtualLinha > _animacao->sprite->imagem->lines - 1)
      {
        _animacao->finalizado = 1;
        _animacao->frameAtualLinha = 0;
      }
    }
  }
}

BM_ANIMACAO *BM_Animacao_procurar_fila(BM_ANIMACAO *_animacao)
{
  BM_ANIMACAO *aux;
  for (aux = animacoes->first; aux != _animacao; aux = aux->next)
  {
    if (aux == NULL)
    {
      return NULL;
    }
  }
  return aux;
}

void BM_Animacao_processar()
{
  BM_ANIMACAO *aux;
  for (aux = animacoes->first; aux != NULL; aux = aux->next)
  {
    if (aux->tempoAtual >= aux->tempoAtualizacao)
    {
      aux->render = 1;
      aux->tempoAtual = 0;
    }
    else
    {
      aux->tempoAtual++;
    }
  }
}