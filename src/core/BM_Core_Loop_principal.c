#include "BM_Core_Loop_principal.h"
#include "BM_Allegro_eventos.h"
#include <allegro5/allegro.h>
#include "BM_Core_Renders.h"
#include "BM_Core_Eventos.h"

//==========================================================================
// Macros
//==========================================================================
#define BOOL int
#define TRUE 1
#define FALSE 0

//==========================================================================
// Prototipos
//==========================================================================
void BM_Loop_iniciarTimer();
void BM_Loop_controlar_fps();
double BM_obterTempoTimer();

//==========================================================================
// Variavel para o controle do tempo de Atualiza��o
//==========================================================================
double BM_Loop_tempoInicial = 0;
int BM_Loop_frame = 0;
BOOL BM_Loop_limitado = TRUE;
BOOL BM_Loop_finalizar = FALSE;

//==========================================================================
// Loop principal
//==========================================================================
void BM_Loop()
{
	BM_CORE_Evento_inicial();
	while (!BM_Loop_finalizar)
	{
		BM_Loop_iniciarTimer();
		if (BM_Eventos_processar() == FECHAR_JOGO)
			BM_Loop_finalizar = TRUE;
		BM_Render_principal();
		BM_Loop_controlar_fps();
	}
}

//==========================================================================
// Controlar a taxa de atualiza��o do jogo
//==========================================================================
void BM_Loop_controlar_fps()
{
	BM_Loop_frame++;
	if (BM_Loop_limitado && (BM_obterTempoTimer() < 1.0 / FPS))
		al_rest((1.0 / FPS) - BM_obterTempoTimer());
}

//==========================================================================
// Iniciar timer para travar o tempo de atualiza��o
//==========================================================================
void BM_Loop_iniciarTimer()
{
	BM_Loop_tempoInicial = al_get_time();
}

//==========================================================================
// Obter tempo decorrido desde o inicio da aplica��o
//==========================================================================
double BM_obterTempoTimer()
{
	return al_get_time() - BM_Loop_tempoInicial;
}
