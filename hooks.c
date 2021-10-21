#include <FreeRTOS.h>
#include <task.h>


void vApplicationStackOverflowHook(xTaskHandle *pxTsk, signed portCHAR *pcTskNm);
void vApplicationStackOverflowHook(xTaskHandle *pxTsk, signed portCHAR *pcTskNm) {
	//taskDISABLE_INTERRUPTS();  // game over
	//for (;;) ;
}