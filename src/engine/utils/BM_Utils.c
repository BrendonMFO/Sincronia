#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 
 * - Função responsavel por verificar o ponteiro informado
 *   esta nulo e disparar 0 caso esteja
 */
void BM_Utils_ponteiro(void *ponteiro, char *mensagem)
{
    if (ponteiro == NULL)
    {
        printf("%s\n", mensagem);
        exit(-1);
    }
}

/**
 * @brief 
 * - Função responsavel por copiar o conteudo de uma string para
 *   a outra
 */
void BM_Utils_copy_string(char *fonte, char *destino)
{
    BM_Utils_ponteiro(fonte, "O ponteiro da fonte esta nulo.");

    destino = (char *)malloc(sizeof(char) * strlen(fonte) + 2);

    BM_Utils_ponteiro(destino, "Nao foi possivel alocar memoria para a copia.");
    
    strcpy(destino, fonte);

}