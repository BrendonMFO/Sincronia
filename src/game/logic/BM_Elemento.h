#ifndef _BM_LOGIC_ELEMENTO_
#define _BM_LOGIC_ELEMENTO_

//==========================================================================
// Enum - Elementos disponiveis
//==========================================================================
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

//==========================================================================
// Estrutura de dados de nivel dos elementos
//==========================================================================
typedef struct BM_ELEMENTOS_INFO_S
{
	int luz;
	int trevas;
	int fogo;
	int agua;
	int terra;
	int ar;
} BM_ELEMENTOS;

//==========================================================================
// Adicionar elementos para a fila de eventos do mouse
//==========================================================================
void BM_Elemento_adicionar_mouse_listener();

//==========================================================================
// Remover elementos da lista de eventos do mouse
//==========================================================================
void BM_Elemento_remover_mouse_listener();

#endif