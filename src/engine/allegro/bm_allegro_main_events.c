#include "bm_allegro_main_events.h"
#include "bm_allegro_mouse_callback_queue.h"

static ALLEGRO_EVENT events_loop;
static ALLEGRO_TIMEOUT timeout_loop;
static ALLEGRO_EVENT_QUEUE *events_queue_loop;

void bm_al_events_queue_execute();
void bm_al_events_listener_init();
int bm_al_events_window_register(ALLEGRO_DISPLAY *_display);

ALLEGRO_EVENT_QUEUE *bm_al_event_get_queue()
{
  return events_queue_loop;
}

int bm_al_events_init(ALLEGRO_DISPLAY *_display)
{
  bm_al_events_window_register(_display);
  bm_al_events_listener_init();
  return 1;
}

int bm_al_events_window_register(ALLEGRO_DISPLAY *_display)
{
  bm_al_create_event_queue(&events_queue_loop);
  al_register_event_source(events_queue_loop, al_get_display_event_source(_display));
  return 1;
}

void bm_al_events_listener_init()
{
  al_init_timeout(&timeout_loop, 0.15);
  al_register_event_source(events_queue_loop, al_get_keyboard_event_source());
  al_register_event_source(events_queue_loop, al_get_mouse_event_source());
}

int bm_al_events_loop_process()
{
  int has_events = al_wait_for_event_until(events_queue_loop, &events_loop, &timeout_loop);
  if (has_events && events_loop.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
  {
    return SHUTDOWN;
  }
  bm_al_events_queue_execute();
  return LOOP;
}

void bm_al_events_queue_execute()
{
  BM_EVENT_CALLBACK *aux, *aux2;

  if (bm_events_get_callback_queue() == NULL)
  {
    return;
  }

  for (aux = bm_events_get_callback_queue()->first; aux != NULL;)
  {
    aux->callback(events_loop, aux->parameter);

    if (aux->active != 0)
    {
      aux = aux->next;
      continue;
    }

    if (aux->next == NULL)
    {
      aux = NULL;
    }
    else
    {
      aux2 = aux->next;
      free(aux->parameter);
      free(aux);
      aux = aux2;
    }
  }
}
