//========================================================================
// Brendon Mike Feliciano de Oliveira - 528489
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BM_Utils.h"
#include "BM_Core_Eventos.h"

//=========================================================================
// Prototipos
//=========================================================================
BM_Core_EVENTOS_REGISTRO *BM_Core_Eventos_procurar(char *evento);
void BM_Core_Eventos_adicionar_eventos(BM_Core_EVENTOS_REGISTRO *registro);

/**
 * @brief 
 * - Pilha que contem todos os eventos registrados na engine
 */
BM_Core_EVENTOS_PILHA *pilha_eventos;

/**
 * @brief 
 * - Função responsavel por alocar e iniciar a pilha de eventos registrados
 */
void BM_Core_Eventos_iniciar()
{
    pilha_eventos = (BM_Core_EVENTOS_PILHA *)malloc(sizeof(BM_Core_EVENTOS_PILHA));

    BM_Utils_ponteiro(pilha_eventos, "Erro: Nao foi possivel alocar memoria para a pilha de eventos");

    pilha_eventos->top = NULL;
}

/**
 * @brief 
 * - Função responsavel por adicionar um novo registro de eventos
 */
void BM_Core_Eventos_registrar(char *evento, void (*funcao)())
{
    BM_Utils_ponteiro(evento, "O ponteiro de nome esta nulo.");
    
    BM_Utils_ponteiro(funcao, "O ponteiro de funcao está nulo.");

    BM_Core_EVENTOS_REGISTRO *registro = (BM_Core_EVENTOS_REGISTRO *)malloc(sizeof(BM_Core_EVENTOS_REGISTRO));

    BM_Utils_ponteiro(registro, "Erro: Nao foi possivel alocar memoria para o registro de eventos.");

    BM_Utils_copy_string(evento, registro->evento);

    registro->funcao = funcao;

    registro->next = NULL;

    BM_Core_Eventos_adicionar_eventos(registro);
}

/**
 * @brief 
 * - Função responsavel por executar um determinado evento com o nome
 *   informado
 */
void BM_Core_Eventos_executar(char *evento)
{
    BM_Core_EVENTOS_REGISTRO *registro = BM_Core_Eventos_procurar(evento);

    registro->funcao();
}

/**
 * @brief 
 * - Adicionar novo registro de eventos na pilha de eventos da engine
 */
void BM_Core_Eventos_adicionar_eventos(BM_Core_EVENTOS_REGISTRO *registro)
{
    BM_Utils_ponteiro(registro, "O ponteiro de registro esta nulo.");

    registro->next = pilha_eventos->top;

    pilha_eventos->top = registro;
}

/**
 * @brief 
 * - Função responsavel por buscar um evento que tenha o nome informado
 */
BM_Core_EVENTOS_REGISTRO *BM_Core_Eventos_procurar(char *evento)
{
    BM_Core_EVENTOS_REGISTRO *temp;

    for (temp = pilha_eventos->top; temp != NULL; temp = temp->next)
    {
        if (strcmp(evento, temp->evento) == 0)
        {
            return temp;
        }
    }

    BM_Utils_ponteiro(temp, "Erro: O evento informado nao foi encontrado.");

    return NULL;
}