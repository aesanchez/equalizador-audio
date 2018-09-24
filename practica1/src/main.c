#include "sapi.h"
#include "clock.h"

uint16_t counter = 0;
char time_uart[11];
char time_lcd[9];

void lcd_loading(void);

void tick_handler()
{
	if(counter++ != 20)
		return;
	//paso un segundo
	counter = 0;
	clock_tick();
	clock_get_time_as_str(time_uart);
	clock_get_time_as_str(time_lcd);
	lcdClear();
	lcdGoToXY(1,1);
	lcdSendStringRaw(time_lcd);
	//fix para imprimir en serial
	time_uart[8] = '\r';
	time_uart[9] = '\n';
	time_uart[10] = '\0';//fin de string

   	uartWriteString( UART_USB, time_uart );
}

int main(void)
{
	/* Inicializar la placa */
	boardConfig();
	/* Inicializar UART_USB a 115200 baudios */
   	uartConfig( UART_USB, 115200 );
	/* Inicializar LCD: 16x2 caracteres de 5x8 px */
	lcdInit( 16, 2, 5, 8 );
	/* Cool loading animation*/
	lcd_loading();
	/* ejecutar periodicamente un tick cada 1-50ms (definido por la libreria) */
	tickConfig(50);
	/* agregar(enganchar) una funcion a la interrupcion de tick */
	tickCallbackSet(tick_handler, (void*)NULL);

	while (1){
	}
	return 0;
}

void lcd_loading(void){
	lcdClear();
	lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1
	lcdSendStringRaw( "Hello World!" );
	lcdGoToXY( 1, 2 ); //Siguiente linea
	lcdSendStringRaw("Loading");
	delay(500);
	lcdSendStringRaw(".");
	delay(500);
	lcdSendStringRaw(".");
	delay(500);
	lcdSendStringRaw(".");
	delay(500);
	lcdSendStringRaw(".");
	delay(500);
	lcdSendStringRaw(".");
	delay(500);
	lcdClear();
	lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1
}