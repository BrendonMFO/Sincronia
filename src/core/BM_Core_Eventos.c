#include "BM_Core_Eventos.h"
#include "BM_Campo.h"
#include "BM_Allegro_eventos_mouse.h"
#include "BM_Recursos.h"
#include "BM_Core_Renders.h"
#include "BM_Elemento.h"
#include "BM_Player.h"
#include "BM_Player_IA.h"
#include "BM_Recursos_Animacao.h"
#include "BM_Rodadas.h"
#include "BM_Hexagono.h"

//==========================================================================
// Variaveis
//==========================================================================
int executando = FALSE;

//==========================================================================
// Prototipos
//==========================================================================
void BM_Evento_alvo(void *_parametro);
void BM_Evento_jogador(void *_parametro);
void BM_Evento_escolha(void *_parametro);
void BM_Evento_tutorial(void *_parametro);
void BM_Evento_reiniciar(void *_parametro);
void BM_CORE_Check_Executando();
void BM_Iniciar();

//==========================================================================
// Iniciar jogo
//==========================================================================
void BM_Iniciar()
{
	BM_CORE_Check_Executando();
	BM_Render_remover_funcao(BM_Render_tutorial);
	BM_Eventos_Funcoes_remover(BM_Evento_tutorial);
	BM_Render_adicionar_funcao(BM_Render_rodada, NULL);
	BM_Eventos_Funcoes_adicionar(BM_Evento_jogador, NULL);
}

//==========================================================================
// Verificar se o jogo já foi iniciado, se não iniciar as operações de inicio
//==========================================================================
void BM_CORE_Check_Executando()
{
	if (executando == FALSE)
	{
		BM_Rodada_set(50);
		BM_Player_iniciar_valores(0);
		BM_IA_iniciar_valores(BM_Campo_getCampo()->quantidade - 1);
		executando = TRUE;
	}
}

//==========================================================================
// Evento inicial
//==========================================================================
void BM_CORE_Evento_inicial()
{
	executando = FALSE;
	BM_Eventos_Funcoes_adicionar(BM_Evento_tutorial, NULL);
	BM_Render_adicionar_funcao(BM_Render_tutorial, NULL);
}

//==========================================================================
// Verificar se o jogo possue um vencedor
//==========================================================================
void BM_Jogo_verificar_fim()
{
	if (BM_Rodada_get_restantes() == 0 ||
		BM_Player_getJogador()->quantidadeTerritorio == 0 ||
		BM_Player_getIAPlayer()->quantidadeTerritorio == 0)
	{
		BM_Render_adicionar_funcao(BM_Render_resultado, NULL);
		BM_Eventos_Funcoes_remover(BM_Evento_jogador);
		BM_Eventos_Funcoes_adicionar(BM_Evento_reiniciar, NULL);
		executando = FALSE;
	}
}

//==========================================================================
// Eventos disparados na tela de tutorial
//==========================================================================
void BM_Evento_tutorial(void *_parametro)
{
	ALLEGRO_EVENT aux = BM_Eventos_obter_evento();
	switch (aux.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (aux.keyboard.keycode)
		{
		case ALLEGRO_KEY_I:
			BM_Iniciar();
			break;
		case ALLEGRO_KEY_ENTER:
			if (BM_Render_obter_tutorial() == 9)
				BM_Iniciar();
			else
				BM_Render_avancar_tutorial();
			break;
		}
	}
}

//==========================================================================
// Eventos disparados pelo jogador
//==========================================================================
void BM_Evento_jogador(void *_parametro)
{
	ALLEGRO_EVENT aux = BM_Eventos_obter_evento();
	if (BM_IA_get_executando() == FALSE)
	{
		switch (aux.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			BM_Player_mover(BM_Player_getJogador(), aux.mouse.x, aux.mouse.y);
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (aux.keyboard.keycode)
			{
			case ALLEGRO_KEY_A:
				if (BM_Campo_getCampo()->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado == JOGADOR)
				{
					if (BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_ALVO) > 0)
					{
						BM_Hexagono_marcar_sincronia(JOGADOR);
						BM_Eventos_Funcoes_remover(BM_Evento_jogador);
						BM_Eventos_Funcoes_adicionar(BM_Evento_alvo, NULL);
					}
				}
				break;
			case ALLEGRO_KEY_S:
				if (BM_Campo_getCampo()->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado != ADVERSARIO)
				{
					BM_Elemento_adicionar_mouse_listener();
					BM_Render_adicionar_funcao(BM_Render_elementos, NULL);
					BM_Eventos_Funcoes_remover(BM_Evento_jogador);
					BM_Eventos_Funcoes_adicionar(BM_Evento_escolha, NULL);
				}
				break;
			case ALLEGRO_KEY_T:
				BM_Render_reiniciar_tutorial();
				BM_Eventos_Funcoes_remover(BM_Evento_jogador);
				BM_Eventos_Funcoes_adicionar(BM_Evento_tutorial, NULL);
				BM_Render_remover_funcao(BM_Render_rodada);
				BM_Render_adicionar_funcao(BM_Render_tutorial, NULL);
			}
			break;
		}
	}
}

//==========================================================================
// Eventos quando a opção de ataque esta selecionada
//==========================================================================
void BM_Evento_alvo(void *_parametro)
{
	ALLEGRO_EVENT aux = BM_Eventos_obter_evento();
	BM_Campo *campo = BM_Campo_getCampo();
	BM_HEXAGONO *hexagonoClick;
	switch (aux.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		hexagonoClick = BM_Hexagono_click(aux.mouse.x, aux.mouse.y);
		if (hexagonoClick != NULL)
		{
			if (hexagonoClick->estado == ADVERSARIO)
			{
				switch (BM_Hexagono_batalha(hexagonoClick->id, BM_Player_getJogador()->hexagonoAtual, JOGADOR, ADVERSARIO))
				{
				case VITORIA_ATAQUE:
					BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);
					BM_Hexagono_desmarcar_sincronia(JOGADOR);
					hexagonoClick->estado = JOGADOR;
					BM_Player_getJogador()->hexagonoAtual = hexagonoClick->id;
					BM_Player_getJogador()->quantidadeTerritorio++;
					BM_Player_getIAPlayer()->quantidadeTerritorio--;
					break;
				case VITORIA_DEFESA:
					BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);
					BM_Hexagono_desmarcar_sincronia(JOGADOR);
					campo->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado = ADVERSARIO;
					BM_Player_getJogador()->quantidadeTerritorio--;
					BM_Player_getIAPlayer()->quantidadeTerritorio++;
					break;
				case EMPATE:
					BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);
					BM_Hexagono_desmarcar_sincronia(JOGADOR);
					break;
				}
				BM_Eventos_Funcoes_remover(BM_Evento_alvo);
				BM_Eventos_Funcoes_adicionar(BM_Evento_jogador, NULL);
				if (BM_Player_getIAPlayer()->quantidadeTerritorio > 0)
					BM_IA_disparar();
				else
					BM_Jogo_verificar_fim();
			}
		}
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (aux.keyboard.keycode)
		{
		case ALLEGRO_KEY_A:
			BM_Hexagono_marcar_alvos(BM_Player_getJogador()->hexagonoAtual, HEXAGONO_NORMAL);
			BM_Hexagono_desmarcar_sincronia(JOGADOR);
			BM_Eventos_Funcoes_remover(BM_Evento_alvo);
			BM_Eventos_Funcoes_adicionar(BM_Evento_jogador, NULL);
			break;
		}
		break;
	}
}

//==========================================================================
// Eventos na tela de seleção de elementos
//==========================================================================
void BM_Evento_escolha(void *_parametro)
{
	ALLEGRO_EVENT aux = BM_Eventos_obter_evento();
	BM_Campo *campo = BM_Campo_getCampo();
	BM_EVENTO_MOUSE *mouse;
	int elemento;
	switch (aux.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		mouse = BM_Eventos_Mouse_processar(aux.mouse.x, aux.mouse.y);
		if (mouse != NULL)
		{
			elemento = *(int *)mouse->opcional;
			if (BM_Player_disponibilidade_elemento(elemento) == TRUE)
			{
				if (campo->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado == NEUTRO)
					BM_Player_getJogador()->quantidadeTerritorio++;
				BM_Player_checar_elemento(elemento);
				campo->hexagonos[BM_Player_getJogador()->hexagonoAtual].elemento = elemento;
				campo->hexagonos[BM_Player_getJogador()->hexagonoAtual].estado = JOGADOR;
				BM_Elemento_remover_mouse_listener();
				BM_Render_remover_funcao(BM_Render_elementos);
				BM_Eventos_Funcoes_remover(BM_Evento_escolha);
				BM_Eventos_Funcoes_adicionar(BM_Evento_jogador, NULL);
				BM_IA_disparar();
			}
		}
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (aux.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			BM_Elemento_remover_mouse_listener();
			BM_Render_remover_funcao(BM_Render_elementos);
			BM_Eventos_Funcoes_remover(BM_Evento_escolha);
			BM_Eventos_Funcoes_adicionar(BM_Evento_jogador, NULL);
			break;
		}
		break;
	}
}

//==========================================================================
// Reiniciar jogo
//==========================================================================
void BM_Evento_reiniciar(void *_parametro)
{
	ALLEGRO_EVENT aux = BM_Eventos_obter_evento();
	switch (aux.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (aux.keyboard.keycode)
		{
		case ALLEGRO_KEY_R:
			BM_Campo_redefinir();
			BM_IA_iniciar_valores(BM_Campo_getCampo()->quantidade - 1);
			BM_Eventos_Funcoes_remover(BM_Evento_reiniciar);
			BM_Render_remover_funcao(BM_Render_resultado);
			BM_Iniciar();
			break;
		}
		break;
	}
}