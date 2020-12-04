#include <stdio.h>
#include "bm_allegro.h"
#include "BM_Recursos.h"
#include "bm_display.h"
#include "BM_Recursos_Conteudo.h"

#define NEW_SPRITE(CAMINHO, LINHA, COLUNA) BM_VETOR_SPRITES[++indexSprite] = carregar_sprite((CAMINHO), (LINHA), (COLUNA))
#define NEW_IMAGE(CAMINHO) BM_VETOR_IMAGENS[++indexTutorial] = carregar_sprite((CAMINHO), 1, 1);
#define NEW_FONT(FONTE, TAMANHO, FLAG) bm_al_load_ttf_font(&BM_VETOR_FONTES[++indexFonte], (FONTE), ((TAMANHO) * (bm_get_display().width * bm_get_display().height)) / (1600 * 920), (FLAG));

static int indexFonte = -1;
static int indexSprite = -1;
static int indexTutorial = -1;
static BM_SPRITES *BM_VETOR_SPRITES[QUANTIDADE_SPRITES];
static BM_SPRITES *BM_VETOR_IMAGENS[QUANTIDADE_IMAGENS];
static ALLEGRO_FONT *BM_VETOR_FONTES[QUANTIDADE_FONTES];

void BM_Recursos_carregar_fonte();
void BM_Recursos_carregar_sprite();
void BM_Recursos_carregar_imagens();
int BM_Recursos_checar_arquivos();
BM_SPRITES *carregar_sprite(char *_arquivo, int _lines, int _columns);

BM_SPRITES *BM_Recursos_obter_recurso(int _indice)
{
  return BM_VETOR_SPRITES[_indice];
}

ALLEGRO_FONT *BM_Recursos_obter_fonte(int _indice)
{
  return BM_VETOR_FONTES[_indice];
}

BM_SPRITES *BM_Recursos_obter_imagem(int _indice)
{
  return BM_VETOR_IMAGENS[_indice];
}

int bm_resource_load()
{
  BM_Recursos_carregar_sprite();
  BM_Recursos_carregar_fonte();
  BM_Recursos_carregar_imagens();
  return BM_Recursos_checar_arquivos();
}

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

void BM_Recursos_carregar_fonte()
{
  NEW_FONT(RESOURCE("Fontes/ALBAS___.TTF"), 100, 0);
  NEW_FONT(RESOURCE("Fontes/ALBAS___.TTF"), 40, 0);
}

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

BM_SPRITES *carregar_sprite(char *_arquivo, int _lines, int _columns)
{
  BM_SPRITES *temp = (BM_SPRITES *)malloc(1 * sizeof(BM_SPRITES));
  temp->image = bm_al_load_bitmap(_arquivo, _lines, _columns);
  if (temp->image == NULL)
  {
    fprintf(stderr, "0 ao carregar Sprite : %s\n", _arquivo);
    return NULL;
  }
  temp->ajusteW = ((bm_al_bitmap_width(temp->image->bitmap) / _columns) * bm_get_display().width) / 1600;
  temp->ajusteH = ((bm_al_bitmap_height(temp->image->bitmap) / _lines) * bm_get_display().height) / 920;
  return temp;
}

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

void BM_Recursos_destruir()
{
  int i;
  for (i = 0; i < QUANTIDADE_SPRITES; i++)
  {
    if (BM_VETOR_SPRITES[i] != NULL)
    {
      al_destroy_bitmap(BM_VETOR_SPRITES[i]->image->bitmap);
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
      al_destroy_bitmap(BM_VETOR_IMAGENS[i]->image->bitmap);
    }
  }
}