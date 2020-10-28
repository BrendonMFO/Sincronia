#ifndef _BM_ALLEGRO_
#define _BM_ALLEGRO_

#include <png.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

int bm_al_init();

int bm_al_create_display(ALLEGRO_DISPLAY **_display, int x, int y);

int bm_al_create_event_queue(ALLEGRO_EVENT_QUEUE **_event_queue);

int bm_al_load_ttf_font(ALLEGRO_FONT **_font, char *font, int size, int flags);

#endif