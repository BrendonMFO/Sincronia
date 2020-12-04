#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bm_utils.h"
#include "bm_core_events.h"

static BM_CORE_EVENTS_STACK *events_stack;

BM_CORE_EVENTS_REGISTER *bm_core_events_search(char *event);
void bm_core_events_add(BM_CORE_EVENTS_REGISTER *event_register);

void bm_core_events_init()
{
  events_stack = (BM_CORE_EVENTS_STACK *)malloc(sizeof(BM_CORE_EVENTS_STACK));

  bm_utils_pointer(events_stack, "Error: Could not allocate memory events_stack");

  events_stack->top = NULL;
}

void bm_core_events_register(char *event, void (*callback)())
{
  bm_utils_pointer(event, "Error: Null pointer detected event");

  bm_utils_pointer(callback, "Error: Null pointer detected callback");

  BM_CORE_EVENTS_REGISTER *event_register = (BM_CORE_EVENTS_REGISTER *)malloc(sizeof(BM_CORE_EVENTS_REGISTER));

  bm_utils_pointer(event_register, "Error: Could not allocate memory event_register");

  bm_utils_copy_string(event, event_register->event);

  event_register->callback = callback;

  event_register->next = NULL;

  bm_core_events_add(event_register);
}

void bm_core_events_exec(char *event)
{
  BM_CORE_EVENTS_REGISTER *event_register = bm_core_events_search(event);

  event_register->callback();
}

void bm_core_events_add(BM_CORE_EVENTS_REGISTER *event_register)
{
  bm_utils_pointer(event_register, "Error: Null pointer detected event_register");

  event_register->next = events_stack->top;

  events_stack->top = event_register;
}

BM_CORE_EVENTS_REGISTER *bm_core_events_search(char *event)
{
  BM_CORE_EVENTS_REGISTER *temp;

  for (temp = events_stack->top; temp != NULL; temp = temp->next)
  {
    if (strcmp(event, temp->event) == 0)
    {
      return temp;
    }
  }

  bm_utils_pointer(temp, "Error: Could not find the event");

  return NULL;
}