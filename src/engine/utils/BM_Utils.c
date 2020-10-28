#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void BM_Utils_ponteiro(void *ponteiro, char *mensagem)
{
  if (ponteiro == NULL)
  {
    printf("%s\n", mensagem);
    exit(-1);
  }
}

void BM_Utils_copy_string(char *font, char *destino)
{
  BM_Utils_ponteiro(font, "O ponteiro da font esta nulo.");

  destino = (char *)malloc(sizeof(char) * strlen(font) + 2);

  BM_Utils_ponteiro(destino, "Nao foi possivel alocar memoria para a copia.");

  strcpy(destino, font);
}