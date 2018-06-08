#include <stdlib.h>
#include "BM_Allegro.h"
#include "BM_Socket_events.h"

/**
 * @brief 
 */
static communication_callback_list_t callback_list;

/**
 * @brief 
 */
ALLEGRO_MUTEX *sem_var;

/**
 * @brief 
 * 
 */
void BM_Socket_events_init()
{
    callback_list.first = NULL;
    callback_list.last = NULL;
    sem_var = al_create_mutex();
}

/**
 * @brief 
 * 
 * @param type 
 * @param funcao 
 */
void BM_Socket_events_push(int type, void (*funcao)(player_message_t *))
{
    communication_callback_t *new_callback = (communication_callback_t *)malloc(sizeof(communication_callback_t));
    if (new_callback == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new_callback->type = type;
    new_callback->funcao = funcao;

    al_lock_mutex(sem_var);
    if (callback_list.first == NULL && callback_list.last == NULL)
    {
        new_callback->prev = NULL;
        new_callback->next = NULL;
        callback_list.first = new_callback;
        callback_list.last = new_callback;
    }
    else
    {
        new_callback->prev = callback_list.last;
        callback_list.last->next = new_callback;
        callback_list.last = new_callback;
    }
    al_unlock_mutex(sem_var);
}

/**
 * @brief 
 * 
 */
void BM_Socket_events_pop(int type, void (*funcao)(player_message_t *))
{
    communication_callback_t *callback;

    al_lock_mutex(sem_var);

    for (callback = callback_list.first; callback != NULL; callback = callback->next)
    {
        if (callback->funcao == funcao && callback->type == type)
        {
            break;
        }
    }

    if (callback != NULL)
    {
        if (callback_list.first == callback && callback_list.last == callback)
        {
            callback_list.first = NULL;
            callback_list.last = NULL;
        }
        else
        {
            if (callback->prev != NULL)
            {
                callback->prev->next = callback->next;
            }
            else
            {
                callback_list.first = callback->next;
            }

            if (callback->next != NULL)
            {
                callback->next->prev = callback->prev;
            }
            else
            {
                callback_list.last = callback->prev;
            }
        }
        free(callback);
    }

    al_unlock_mutex(sem_var);
}

/**
 * @brief 
 * 
 * @param type 
 * @param message 
 */
void BM_Socket_events_call(int type, player_message_t *message)
{
    communication_callback_t *callback;
    for (callback = callback_list.first; callback != NULL; callback = callback->next)
    {
        if (callback->type == type)
        {
            callback->funcao(message);
        }
    }
}