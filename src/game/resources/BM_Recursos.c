#include "BM_Recursos.h"
#include "BM_Recursos_Conteudo.h"
#include "BM_Allegro.h"
#include "BM_Allegro_janela.h"
#include <stdio.h>

//==========================================================================
// Macros
//==========================================================================
#define NEW_SPRITE(CAMINHO, LINHA, COLUNA) BM_VETOR_SPRITES[++indexSprite] = carregar_sprite((CAMINHO), (LINHA), (COLUNA))
#define NEW_IMAGE(CAMINHO) BM_VETOR_IMAGENS[++indexTutorial] = carregar_sprite((CAMINHO), 1, 1);
#define NEW_FONT(FONTE, TAMANHO, FLAG) BM_Allegro_carregar_font(&BM_VETOR_FONTES[++indexFonte], (FONTE), ((TAMANHO) * (BM_Janela_obter_dados().largura * BM_Janela_obter_dados().altura)) / (1600 * 920), (FLAG));

//==========================================================================
// Variaveis globais com os recursos disponiveis
//==========================================================================
BM_SPRITES *BM_VETOR_SPRITES[QUANTIDADE_SPRITES];
BM_SPRITES *BM_VETOR_IMAGENS[QUANTIDADE_IMAGENS];
ALLEGRO_FONT *BM_VETOR_FONTES[QUANTIDADE_FONTES];
int indexSprite = -1;
int indexTutorial = -1;
int indexFonte = -1;

//==========================================================================
// Prototipos
//==========================================================================
void BM_Recursos_carregar_sprite();
void BM_Recursos_carregar_fonte();
void BM_Recursos_carregar_imagens();
int BM_Recursos_checar_arquivos();
BM_SPRITES *carregar_sprite(char *_arquivo, int _framesLinhas, int _framesColunas);

//==========================================================================
// Obter sprite com os recursos visuais carregados
//==========================================================================
BM_SPRITES *BM_Recursos_obter_recurso(int _indice)
{
	return BM_VETOR_SPRITES[_indice];
}

//==========================================================================
// Obter fonte
//==========================================================================
ALLEGRO_FONT *BM_Recursos_obter_fonte(int _indice)
{
	return BM_VETOR_FONTES[_indice];
}

//==========================================================================
// Obter sprite do tutorial
//==========================================================================
BM_SPRITES *BM_Recursos_obter_imagem(int _indice)
{
	return BM_VETOR_IMAGENS[_indice];
}

//==========================================================================
// Carregar Sprites
//==========================================================================
int BM_Recursos_carregar_recursos()
{
	BM_Recursos_carregar_sprite();
	BM_Recursos_carregar_fonte();
	BM_Recursos_carregar_imagens();
	return BM_Recursos_checar_arquivos();
}

//==========================================================================
// Carregar Sprites
//==========================================================================
void BM_Recursos_carregar_sprite()
{
	NEW_SPRITE(RESOURCE("Fases/Mapa_01.bmp"), 1, 1);
	NEW_SPRITE(RESOURCE("Sprites/Hexagono_1.png"), 7, 3);
	NEW_SPRITE(RESOURCE("Sprites/Player.png"), 1, 1);
	NEW_SPRITE(RESOURCE("Sprites/Hexagono_Alvo.png"), 1, 5);
	NEW_SPRITE(RESOURCE("Sprites/Elementos.png"), 1, 6);
	NEW_SPRITE(RESOURCE("Sprites/IA.png"), 1, 1);
	NEW_SPRITE(RESOURCE("Sprites/Animacoes/light_004.png"), 5, 5);
	NEW_SPRITE(RESOURCE("Sprites/Animacoes/darkness_002.png"), 6, 5);
	NEW_SPRITE(RESOURCE("Sprites/Animacoes/fire_002.png"), 5, 5);
	NEW_SPRITE(RESOURCE("Sprites/Animacoes/water_005.png"), 6, 5);
	NEW_SPRITE(RESOURCE("Sprites/Animacoes/earth_002.png"), 4, 5);
	NEW_SPRITE(RESOURCE("Sprites/Animacoes/wind_003.png"), 6, 5);
}

//==========================================================================
// Carregar Fontes
//==========================================================================
void BM_Recursos_carregar_fonte()
{
	NEW_FONT(RESOURCE("Fontes/ALBAS___.TTF"), 100, 0);
	NEW_FONT(RESOURCE("Fontes/ALBAS___.TTF"), 40, 0);
}

//==========================================================================
// Carregar arquivos de tutorial
//==========================================================================
void BM_Recursos_carregar_imagens()
{
	NEW_IMAGE(RESOURCE("Images/Img0.png"));
	NEW_IMAGE(RESOURCE("Images/Img1.png"));
	NEW_IMAGE(RESOURCE("Images/Img2.png"));
	NEW_IMAGE(RESOURCE("Images/Img3.png"));
	NEW_IMAGE(RESOURCE("Images/Img4.png"));
	NEW_IMAGE(RESOURCE("Images/Img5.png"));
	NEW_IMAGE(RESOURCE("Images/Img6.png"));
	NEW_IMAGE(RESOURCE("Images/Img7.png"));
	NEW_IMAGE(RESOURCE("Images/Img8.png"));
	NEW_IMAGE(RESOURCE("Images/Img9.png"));
	NEW_IMAGE(RESOURCE("Images/Img10.png"));
}

//==========================================================================
// Carregar Sprites
//==========================================================================
BM_SPRITES *carregar_sprite(char *_arquivo, int _framesLinhas, int _framesColunas)
{
	BM_SPRITES *temp = (BM_SPRITES *)malloc(1 * sizeof(BM_SPRITES));
	temp->imagem = BM_Allegro_carregar_imagem(_arquivo, _framesLinhas, _framesColunas);
	if (temp->imagem == NULL)
	{
		fprintf(stderr, "0 ao carregar Sprite : %s\n", _arquivo);
		return NULL;
	}
	temp->ajusteW = ((BM_Allegro_largura_da_imagem(temp->imagem->bitmap) / _framesColunas) * BM_Janela_obter_dados().largura) / 1600;
	temp->ajusteH = ((BM_Allegro_altura_da_imagem(temp->imagem->bitmap) / _framesLinhas) * BM_Janela_obter_dados().altura) / 920;
	return temp;
}

//==========================================================================
// Checar se todos os arquivos foram carregados
//==========================================================================
int BM_Recursos_checar_arquivos()
{
	int i;
	for (i = 0; i < QUANTIDADE_SPRITES; i++)
	{
		if (BM_VETOR_SPRITES[i] == NULL)
		{
			printf("Erro: Nao foi possivel carregar todos os sprites\n");
			return 0;
		}
	}
	for (i = 0; i < QUANTIDADE_FONTES; i++)
	{
		if (BM_VETOR_FONTES[i] == NULL)
		{
			printf("Erro: Nao foi possivel carregar todas as fontes\n");
			return 0;
		}
	}
	for (i = 0; i < QUANTIDADE_IMAGENS; i++)
	{
		if (BM_VETOR_IMAGENS[i] == NULL)
		{
			printf("Erro: Nao foi possivel carregar todas as imagens\n");
			return 0;
		}
	}
	return 1;
}

//==========================================================================
// Destruir arquivos
//==========================================================================
void BM_Recursos_destruir()
{
	int i;
	for (i = 0; i < QUANTIDADE_SPRITES; i++)
	{
		if (BM_VETOR_SPRITES[i] != NULL)
		{
			al_destroy_bitmap(BM_VETOR_SPRITES[i]->imagem->bitmap);
		}
	}
	for (i = 0; i < QUANTIDADE_FONTES; i++)
	{
		if (BM_VETOR_FONTES[i] != NULL)
		{
			al_destroy_font(BM_VETOR_FONTES[i]);
		}
	}
	for (i = 0; i < QUANTIDADE_IMAGENS; i++)
	{
		if (BM_VETOR_IMAGENS[i] != NULL)
		{
			al_destroy_bitmap(BM_VETOR_IMAGENS[i]->imagem->bitmap);
		}
	}
}