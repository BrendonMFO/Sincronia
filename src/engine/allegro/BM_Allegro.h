#ifndef _BM_ALLEGRO_
#define _BM_ALLEGRO_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <png.h>

//==========================================================================
// Funçao - Iniciar Allegro
//==========================================================================
int BM_Allegro_iniciar();

//==========================================================================
// Funçao - Iniciar janela
//==========================================================================
int BM_Allegro_criar_janela(ALLEGRO_DISPLAY **_window, int x, int y);

//==========================================================================
// Funçao - Instanciar mouse do sistema na aplicação
//==========================================================================
int BM_Allegro_iniciar_mouse(ALLEGRO_DISPLAY **_janela, int flags);

//==========================================================================
// Funçao - Iniciar evento
//==========================================================================
int BM_Allegro_criar_eventos(ALLEGRO_EVENT_QUEUE **_evento);

//==========================================================================
// Funçao - Carregar font
//==========================================================================
int BM_Allegro_carregar_font(ALLEGRO_FONT **_font, char *fonte, int tamanho, int flags);

#endif