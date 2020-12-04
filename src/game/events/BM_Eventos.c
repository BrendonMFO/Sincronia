#include "BM_Render.h"
#include "BM_Eventos.h"
#include "BM_Communication_Send.h"
#include "bm_core_loop.h"

void BM_Core_Evento_inicial()
{
  BM_Eventos_Tutorial_registrar();
  BM_Communication_Send_connection("Player");
}
