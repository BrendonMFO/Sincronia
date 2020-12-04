#include "bm_display.h"
#include "bm_core_load.h"
#include "bm_allegro_bitmap.h"
#include "bm_core_loop.h"

int main(int argc, char *argv[])
{
  ALLEGRO_DISPLAY *janela = NULL;
  int width, height, flag;

  if (argc == 4)
  {
    sscanf(argv[1], "%d", &width);
    sscanf(argv[2], "%d", &height);
    sscanf(argv[3], "%d", &flag);
  }
  else
  {
    width = 600;
    height = 480;
    flag = 0;
  }
  bm_display_init(width, height);

  if (bm_core_load(janela) == 0)
  {
    getchar();
    return -1;
  }

  if (flag == 1)
  {
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  }
  bm_al_create_display(&janela, width, height);
  bm_al_events_init(janela);
  al_clear_to_color(al_map_rgb(255, 255, 255));

  bm_loop(janela);

  BM_Recursos_destruir();
  al_destroy_display(janela);

  return 0;
}
