//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#ifndef _BM_MAIN_EVENTOS_
#define _BM_MAIN_EVENTOS_

/**
 * @brief 
 * - Estrutura de dados que contem os dados para registrar
 *   um novo evento na pilha de eventos chamados da engine
 */
typedef struct BM_Core_EVENTOS_REGISTRO_S
{
    char *evento;
    void (*funcao)();
    struct BM_Core_EVENTOS_REGISTRO_S *next;
} BM_Core_EVENTOS_REGISTRO;

/**
 * @brief 
 * - Estrutura de dados que representa a pilha de chamada de
 *   eventos que devem ser executadas
 */
typedef struct BM_Core_EVENTOS_PILHA_S
{
    BM_Core_EVENTOS_REGISTRO *top;
} BM_Core_EVENTOS_PILHA;

/**
 * @brief 
 * - Função responsavel por alocar e iniciar a pilha de eventos registrados
 */
void BM_Core_Eventos_iniciar();

/**
 * @brief 
 * - Função responsavel por adicionar um novo registro de eventos
 */
void BM_Core_Eventos_registrar(char *evento, void (*funcao)());

/**
 * @brief 
 * - Função responsavel por executar um determinado evento com o nome
 *   informado
 */
void BM_Core_Eventos_executar(char *evento);

#endif