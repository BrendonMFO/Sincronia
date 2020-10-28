#ifndef _BM_LOGIC_ELEMENTO_
#define _BM_LOGIC_ELEMENTO_

enum BM_ELEMENTO
{
  NAO_ELEMENTAL = 0,
  LUZ,
  TREVAS,
  FOGO,
  AGUA,
  TERRA,
  AR
};

typedef struct BM_ELEMENTOS_INFO_S
{
  int luz;
  int trevas;
  int fogo;
  int agua;
  int terra;
  int ar;
} BM_ELEMENTOS;

void BM_Elemento_adicionar_mouse_listener();

void BM_Elemento_remover_mouse_listener();

#endif