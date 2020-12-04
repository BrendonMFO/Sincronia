#include "bm_socket.h"
#include "bm_core_loop.h"
#include "bm_core_events.h"
#include "bm_core_render.h"
#include <allegro5/allegro.h>
#include "bm_allegro_main_events.h"

static int bm_loop_stop = 0;
static int bm_loop_frame = 0;
static int bm_loop_has_limit = 1;
static double bm_loop_initial_time = 0;
static ALLEGRO_THREAD *thread = NULL, *thread_socket = NULL;

void bm_loop_init_timer();
double bm_loop_get_timer();
void bm_loop_control_fps();
void bm_loop_init_thread();
void *bm_loop_thread_input(ALLEGRO_THREAD *, void *);
void *bm_loop_thread_socket(ALLEGRO_THREAD *, void *);

void bm_loop()
{
  BM_Core_Evento_inicial();
  bm_loop_init_thread();
  BM_Render_inicial();
  while (!bm_loop_stop)
  {
    bm_loop_init_timer();
    BM_Render_loop();
    bm_loop_control_fps();
  }
}

void bm_loop_init_thread()
{
  thread = al_create_thread(bm_loop_thread_input, NULL);
  thread_socket = al_create_thread(bm_loop_thread_socket, NULL);
  al_start_thread(thread);
  al_start_thread(thread_socket);
}

void *bm_loop_thread_input(ALLEGRO_THREAD *thr, void *dados)
{
  while (!bm_loop_stop)
  {
    if (bm_al_events_loop_process() == SHUTDOWN)
    {
      bm_loop_stop = 1;
    }
    al_rest(0.0083F);
  }

  al_destroy_thread(thr);
  return NULL;
}

void *bm_loop_thread_socket(ALLEGRO_THREAD *thr, void *dados)
{
  while (!bm_loop_stop)
  {
    bm_socket_receive();
  }

  al_destroy_thread(thr);
  return NULL;
}

void bm_loop_control_fps()
{
  bm_loop_frame++;
  if (bm_loop_has_limit && (bm_loop_get_timer() < 1.0 / FPS))
  {
    al_rest((1.0 / FPS) - bm_loop_get_timer());
  }
}

void bm_loop_init_timer()
{
  bm_loop_initial_time = al_get_time();
}

double bm_loop_get_timer()
{
  return al_get_time() - bm_loop_initial_time;
}
