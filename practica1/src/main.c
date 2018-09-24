#include "sapi.h"
#include "clock.h"

uint16_t counter = 0;

void tick_handler()
{
	if(counter++ != 20)
		return;
	//paso un segundo
	counter = 0;
	clock_tick();
	char time_str[11];
	clock_get_time_as_str(time_str);
	//fix para imprimir en serial
	time_str[8] = '\r';
	time_str[9] = '\n';
	time_str[10] = '\0';//fin de string

   	uartWriteString( UART_USB, time_str );
}

int main(void)
{
	/* Inicializar la placa */
	boardConfig();
	/* Inicializar UART_USB a 115200 baudios */
   	uartConfig( UART_USB, 115200 );

	/* ejecutar periodicamente un tick cada 1-50ms (definido por la libreria) */
	tickConfig(50);
	/* agregar(enganchar) una funcion a la interrupcion de tick */
	tickCallbackSet(tick_handler, (void*)NULL);

	while (1){
	}
	return 0;
}