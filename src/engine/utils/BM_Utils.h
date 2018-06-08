#ifndef _BM_Core_UTILS_
#define _BM_Core_UTILS_

/**
 * @brief 
 * - Função responsavel por verificar o ponteiro informado
 *   esta nulo e disparar 0 caso esteja
 */
void BM_Utils_ponteiro(void *ponteiro, char *mensagem);

/**
 * @brief 
 * - Função responsavel por copiar o conteudo de uma string para
 *   a outra
 */
void BM_Utils_copy_string(char *fonte, char *destino);

#endif