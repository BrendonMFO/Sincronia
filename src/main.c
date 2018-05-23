#include "BM_Allegro_janela.h"
#include "BM_Allegro_Imagens.h"
#include "BM_Core_Carregar.h"
#include "BM_Core_Loop_principal.h"

int main(int argc, char *argv[])
{
	//==========================================================================
	// Variaveis
	//==========================================================================
	ALLEGRO_DISPLAY *janela = NULL;
	int largura, altura, flag;

	//==========================================================================
	// Definir janela
	//==========================================================================
	if (argc == 4)
	{
		sscanf(argv[1], "%d", &largura);
		sscanf(argv[2], "%d", &altura);
		sscanf(argv[3], "%d", &flag);
	}
	else
	{
		largura = 1280;
		altura = 720;
		flag = FALSE;
	}
	BM_Janela_setar_dados(largura, altura);

	//==========================================================================
	// Carregar dados
	//==========================================================================
	if (BM_CORE_carregar(janela) == ERRO)
	{
		getchar();
		return -1;
	}

	//==========================================================================
	// Criar e configurar janela
	//==========================================================================
	if (flag == TRUE)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	BM_Allegro_criar_janela(&janela, largura, altura);
	BM_Eventos_iniciar(janela);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	//==========================================================================
	// Loop principal
	//==========================================================================
	BM_Loop(janela);

	//==========================================================================
	// Finalizar jogo
	//==========================================================================
	al_destroy_display(janela);
	BM_Recursos_destruir();

	return 0;
}
