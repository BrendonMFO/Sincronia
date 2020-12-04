#ifndef _BM_CORE_EVENTS_
#define _BM_CORE_EVENTS_

typedef struct BM_CORE_EVENTS_REGISTER_S
{
  char *event;
  void (*callback)();
  struct BM_CORE_EVENTS_REGISTER_S *next;
} BM_CORE_EVENTS_REGISTER;

typedef struct BM_CORE_EVENTS_STACK_S
{
  BM_CORE_EVENTS_REGISTER *top;
} BM_CORE_EVENTS_STACK;

void bm_core_events_init();

void bm_core_events_register(char *event, void (*callback)());

void bm_core_events_exec(char *event);

#endif