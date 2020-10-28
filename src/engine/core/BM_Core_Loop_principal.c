#include "BM_Socket.h"
#include "BM_Core_Eventos.h"
#include "BM_Core_Renders.h"
#include <allegro5/allegro.h>
#include "bm_allegro_main_events.h"
#include "BM_Core_Loop_principal.h"

static int BM_Loop_frame = 0;
static int BM_Loop_limitado = 1;
static int BM_Loop_finalizar = 0;
static double BM_Loop_tempoInicial = 0;
static ALLEGRO_THREAD *thread = NULL, *thread_socket = NULL;

void BM_Loop_iniciarTimer();
double BM_obterTempoTimer();
void BM_Loop_controlar_fps();
void BM_Core_iniciar_thread();
void *BM_Core_thread_input(ALLEGRO_THREAD *, void *);
void *BM_Core_thread_socket(ALLEGRO_THREAD *, void *);

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

void BM_Core_iniciar_thread()
{
  thread = al_create_thread(BM_Core_thread_input, NULL);
  thread_socket = al_create_thread(BM_Core_thread_socket, NULL);
  al_start_thread(thread);
  al_start_thread(thread_socket);
}

void *BM_Core_thread_input(ALLEGRO_THREAD *thr, void *dados)
{
  while (!BM_Loop_finalizar)
  {
    if (bm_al_events_loop_process() == SHUTDOWN)
    {
      BM_Loop_finalizar = 1;
    }
    al_rest(0.008333333767950534821F);
  }

  al_destroy_thread(thr);
  return NULL;
}

void *BM_Core_thread_socket(ALLEGRO_THREAD *thr, void *dados)
{
  while (!BM_Loop_finalizar)
  {
    BM_Socket_receive();
  }

  al_destroy_thread(thr);
  return NULL;
}

void BM_Loop_controlar_fps()
{
  BM_Loop_frame++;
  if (BM_Loop_limitado && (BM_obterTempoTimer() < 1.0 / FPS))
  {
    al_rest((1.0 / FPS) - BM_obterTempoTimer());
  }
}

void BM_Loop_iniciarTimer()
{
  BM_Loop_tempoInicial = al_get_time();
}

double BM_obterTempoTimer()
{
  return al_get_time() - BM_Loop_tempoInicial;
}
