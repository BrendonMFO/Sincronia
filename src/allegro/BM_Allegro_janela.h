#ifndef _BM_ALLEGRO_JANELA_
#define _BM_ALLEGRO_JANELA_

//==========================================================================
// Macros
//==========================================================================
#define BM_AJUSTE_XW(X) ((X)*BM_Janela_obter_dados().largura) / 1600
#define BM_AJUSTE_YH(Y) ((Y)*BM_Janela_obter_dados().altura) / 920

//==========================================================================
// Estrutura de dados da janela
//==========================================================================
typedef struct BM_JANELA_S
{
	int largura;
	int altura;
} BM_JANELA;

//==========================================================================
// Obter dados da janela
//==========================================================================
BM_JANELA BM_Janela_obter_dados();

//==========================================================================
// Setar dados da janela
//==========================================================================
void BM_Janela_setar_dados(int _largura, int _altura);

#endif