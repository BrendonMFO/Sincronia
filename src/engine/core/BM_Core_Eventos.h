#ifndef _BM_MAIN_EVENTOS_
#define _BM_MAIN_EVENTOS_

typedef struct BM_Core_EVENTOS_REGISTRO_S
{
  char *evento;
  void (*callback)();
  struct BM_Core_EVENTOS_REGISTRO_S *next;
} BM_Core_EVENTOS_REGISTRO;

typedef struct BM_Core_EVENTOS_PILHA_S
{
  BM_Core_EVENTOS_REGISTRO *top;
} BM_Core_EVENTOS_PILHA;

void BM_Core_Eventos_iniciar();

void BM_Core_Eventos_registrar(char *evento, void (*callback)());

void BM_Core_Eventos_executar(char *evento);

#endif