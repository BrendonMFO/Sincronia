#include <stdlib.h>
#include "bm_utils.h"
#include "bm_allegro.h"
#include "bm_socket_events.h"

static ALLEGRO_MUTEX *sem_var;
static communication_callback_list_t callback_list;

void bm_socket_events_init()
{
    callback_list.first = NULL;
    callback_list.last = NULL;
    sem_var = al_create_mutex();
}

void bm_socket_events_push(int type, void (*callback)(player_message_t *))
{
    communication_callback_t *new_callback = (communication_callback_t *)malloc(sizeof(communication_callback_t));
    bm_utils_pointer(new_callback, "Error: Could not allocate memory new_callback");
    new_callback->type = type;
    new_callback->callback = callback;
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

void bm_socket_events_pop(int type, void (*callback)(player_message_t *))
{
    communication_callback_t *communication_callback;

    al_lock_mutex(sem_var);

    for (communication_callback = callback_list.first; communication_callback != NULL; communication_callback = communication_callback->next)
    {
        if (communication_callback->callback == callback && communication_callback->type == type)
        {
            break;
        }
    }

    if (communication_callback != NULL)
    {
        if (callback_list.first == communication_callback && callback_list.last == communication_callback)
        {
            callback_list.first = NULL;
            callback_list.last = NULL;
        }
        else
        {
            if (communication_callback->prev != NULL)
            {
                communication_callback->prev->next = communication_callback->next;
            }
            else
            {
                callback_list.first = communication_callback->next;
            }

            if (communication_callback->next != NULL)
            {
                communication_callback->next->prev = communication_callback->prev;
            }
            else
            {
                callback_list.last = communication_callback->prev;
            }
        }
        free(communication_callback);
    }

    al_unlock_mutex(sem_var);
}

void bm_socket_events_call(int type, player_message_t *message)
{
    communication_callback_t *callback;
    for (callback = callback_list.first; callback != NULL; callback = callback->next)
    {
        if (callback->type == type)
        {
            callback->callback(message);
        }
    }
}
