#include "bm_allegro.h"

int bm_al_init()
{
  if (!al_init())
  {
    fprintf(stderr, "Error to initiate Allegro graphic mode\n");
    return 0;
  }
  if (!al_install_mouse())
  {
    fprintf(stderr, "Error to initiate Allegro mouse system\n");
    return 0;
  }
  if (!al_install_keyboard())
  {
    fprintf(stderr, "Error to initiate Allegro keyboard system\n");
    return 0;
  }
  if (!al_init_image_addon())
  {
    fprintf(stderr, "Error to initiate Allegro image addon\n");
    return 0;
  }
  if (!al_init_ttf_addon())
  {
    fprintf(stderr, "Error to initiate Allegro ttf addon\n");
    return 0;
  }
  if (!al_init_primitives_addon())
  {
    fprintf(stderr, "Error to initiate Allegro primitives addon\n");
    return 0;
  }
  if (!al_init_font_addon())
  {
    fprintf(stderr, "Error to initiate Allegro font addon\n");
    return 0;
  }
  return 1;
}

int bm_al_create_display(ALLEGRO_DISPLAY **_display, int x, int y)
{
  al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
  *_display = al_create_display(x, y);
  if (!*_display)
  {
    fprintf(stderr, "Error: unable to create a display\n");
    return 0;
  }
  return 1;
}

int bm_al_create_event_queue(ALLEGRO_EVENT_QUEUE **_event_queue)
{
  *_event_queue = al_create_event_queue();
  if (!*_event_queue)
  {
    fprintf(stderr, "Error: unable to initiate the event system\n");
    return 0;
  }
  return 1;
}

int bm_al_load_ttf_font(ALLEGRO_FONT **_font, char *font, int size, int flags)
{
  *_font = al_load_ttf_font(font, size, flags);
  if (!*_font)
  {
    fprintf(stderr, "Error: unable to load - %s\n", font);
    return 0;
  }
  return 1;
}