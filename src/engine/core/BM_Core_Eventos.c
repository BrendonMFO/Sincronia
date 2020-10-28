#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BM_Utils.h"
#include "BM_Core_Eventos.h"

static BM_Core_EVENTOS_PILHA *pilha_eventos;

BM_Core_EVENTOS_REGISTRO *BM_Core_Eventos_procurar(char *evento);

void BM_Core_Eventos_adicionar_eventos(BM_Core_EVENTOS_REGISTRO *registro);

void BM_Core_Eventos_iniciar()
{
  pilha_eventos = (BM_Core_EVENTOS_PILHA *)malloc(sizeof(BM_Core_EVENTOS_PILHA));

  BM_Utils_ponteiro(pilha_eventos, "Erro: Nao foi possivel alocar memoria para a pilha de eventos");

  pilha_eventos->top = NULL;
}

void BM_Core_Eventos_registrar(char *evento, void (*callback)())
{
  BM_Utils_ponteiro(evento, "O ponteiro de nome esta nulo.");

  BM_Utils_ponteiro(callback, "O ponteiro de callback está nulo.");

  BM_Core_EVENTOS_REGISTRO *registro = (BM_Core_EVENTOS_REGISTRO *)malloc(sizeof(BM_Core_EVENTOS_REGISTRO));

  BM_Utils_ponteiro(registro, "Erro: Nao foi possivel alocar memoria para o registro de eventos.");

  BM_Utils_copy_string(evento, registro->evento);

  registro->callback = callback;

  registro->next = NULL;

  BM_Core_Eventos_adicionar_eventos(registro);
}

void BM_Core_Eventos_executar(char *evento)
{
  BM_Core_EVENTOS_REGISTRO *registro = BM_Core_Eventos_procurar(evento);

  registro->callback();
}

void BM_Core_Eventos_adicionar_eventos(BM_Core_EVENTOS_REGISTRO *registro)
{
  BM_Utils_ponteiro(registro, "O ponteiro de registro esta nulo.");

  registro->next = pilha_eventos->top;

  pilha_eventos->top = registro;
}

BM_Core_EVENTOS_REGISTRO *BM_Core_Eventos_procurar(char *evento)
{
  BM_Core_EVENTOS_REGISTRO *temp;

  for (temp = pilha_eventos->top; temp != NULL; temp = temp->next)
  {
    if (strcmp(evento, temp->evento) == 0)
    {
      return temp;
    }
  }

  BM_Utils_ponteiro(temp, "Erro: O evento informado nao foi encontrado.");

  return NULL;
}