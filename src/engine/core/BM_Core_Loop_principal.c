//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include "BM_Socket.h"
#include "BM_Core_Eventos.h"
#include "BM_Core_Renders.h"
#include <allegro5/allegro.h>
#include "BM_Allegro_eventos.h"
#include "BM_Core_Loop_principal.h"

//==========================================================================
// Macros
//==========================================================================
#define BOOL int

//==========================================================================
// Prototipos
//==========================================================================
void BM_Loop_iniciarTimer();
double BM_obterTempoTimer();
void BM_Loop_controlar_fps();
void BM_Core_iniciar_thread();
void *BM_Core_thread_input(ALLEGRO_THREAD *, void *);
void *BM_Core_thread_socket(ALLEGRO_THREAD *, void *);

//==========================================================================
// Variavel para o controle do tempo de Atualização
//==========================================================================
int BM_Loop_frame = 0;
BOOL BM_Loop_limitado = 1;
BOOL BM_Loop_finalizar = 0;
double BM_Loop_tempoInicial = 0;
ALLEGRO_THREAD *thread = NULL, *thread_socket = NULL;

//==========================================================================
// Loop principal
//==========================================================================
void BM_Loop()
{
	BM_Core_Evento_inicial();
	BM_Core_iniciar_thread();
	BM_Render_inicial();
	while (!BM_Loop_finalizar)
	{
		BM_Loop_iniciarTimer();
		BM_Render_loop();
		BM_Loop_controlar_fps();
	}
}

//==========================================================================
/**
 * Iniciar thread responsavel por processar as entradas e saidas de eventos
 * do jogo
 */
//==========================================================================
void BM_Core_iniciar_thread()
{
	thread = al_create_thread(BM_Core_thread_input, NULL);
	thread_socket = al_create_thread(BM_Core_thread_socket, NULL);
	al_start_thread(thread);
	al_start_thread(thread_socket);
}

//==========================================================================
/**
 * Função responsavel por chamar o processamento de eventos do sistema
 */
//==========================================================================
void *BM_Core_thread_input(ALLEGRO_THREAD *thr, void *dados)
{
	while (!BM_Loop_finalizar)
	{
		if (BM_Eventos_processar() == FECHAR_JOGO)
			BM_Loop_finalizar = 1;
		al_rest(0.008333333767950534821F);
	}

	al_destroy_thread(thr);
	return NULL;
}

//==========================================================================
/**
 * @brief 
 * - Função reponsavel por escutar todas as mensagens recebidas do servidor
 */
//==========================================================================
void *BM_Core_thread_socket(ALLEGRO_THREAD *thr, void *dados)
{
	while (!BM_Loop_finalizar)
	{
		BM_Socket_receive();
	}

	al_destroy_thread(thr);
	return NULL;
}

//==========================================================================
// Controlar a taxa de atualização do jogo
//==========================================================================
void BM_Loop_controlar_fps()
{
	BM_Loop_frame++;
	if (BM_Loop_limitado && (BM_obterTempoTimer() < 1.0 / FPS))
		al_rest((1.0 / FPS) - BM_obterTempoTimer());
}

//==========================================================================
// Iniciar timer para travar o tempo de atualização
//==========================================================================
void BM_Loop_iniciarTimer()
{
	BM_Loop_tempoInicial = al_get_time();
}

//==========================================================================
// Obter tempo decorrido desde o inicio da aplicação
//==========================================================================
double BM_obterTempoTimer()
{
	return al_get_time() - BM_Loop_tempoInicial;
}
