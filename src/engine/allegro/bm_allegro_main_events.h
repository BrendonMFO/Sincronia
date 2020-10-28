#ifndef _MAIN_EVENTS_
#define _MAIN_EVENTS_

#include "bm_allegro.h"
#include "bm_allegro_events_callback.h"

enum MAIN_EVENTS
{
  SHUTDOWN = 2,
  LOOP = 3
};

ALLEGRO_EVENT_QUEUE *bm_al_event_get_queue();

int bm_al_events_init(ALLEGRO_DISPLAY *_display);

int bm_al_events_loop_process();

#endif