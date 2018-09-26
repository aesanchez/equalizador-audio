#include "sapi.h"
#include "clock.h"

uint16_t counter = 0;
char time_lcd[11];

void lcd_loading(void);

void tick_handler()
{	
	if(counter++ != 2)
		return;
	//paso una decima de segundo
	counter = 0;
	clock_tick_dsec();
	clock_get_time_as_str(time_lcd);
	lcdGoToXY(4,1);
	lcdSendStringRaw(time_lcd);
}

void mylcdInit( uint16_t lineWidth, uint16_t amountOfLines, 
              uint16_t charWidth, uint16_t charHeight ){
   
   // Configure LCD Pins as Outputs
                 
   lcdConfigPinAsOutput( LCD_HD44780_RS );
   lcdConfigPinAsOutput( LCD_HD44780_RW );
   lcdConfigPinAsOutput( LCD_HD44780_EN );
   
   lcdConfigPinAsOutput( LCD_HD44780_D4 );
   lcdConfigPinAsOutput( LCD_HD44780_D5 );
   lcdConfigPinAsOutput( LCD_HD44780_D6 );
   lcdConfigPinAsOutput( LCD_HD44780_D7 );


   // Configure LCD for 4-bit mode
                 
   lcdPinWrite( LCD_HD44780_RW, OFF );   // RW = 0
   lcdPinWrite( LCD_HD44780_RS, OFF );   // RS = 0
                 
   lcdPinWrite( LCD_HD44780_EN, OFF );   // EN = 0

   lcdDelay_ms( LCD_STARTUP_WAIT_MS );   // Wait for stable power
   
   lcdCommand( 0x33 );                   // Command 0x33 for 4-bit mode
   lcdCommandDelay();                    // Wait
                 
   lcdCommand( 0x32 );                   // Command 0x32 for 4-bit mode
   lcdCommandDelay();                    // Wait
                 
   lcdCommand( 0x28 );                   // Command 0x28 for 4-bit mode
   lcdCommandDelay();                    // Wait
   
   
   // Initialize LCD
                  
   lcdCommand( 0x0C );                   // Command 0x0E for display on, cursor on
   lcdCommandDelay();                    // Wait
                 
   lcdClear();                           // Command for clear LCD
                 
   lcdCommand( 0x06 );                   // Command 0x06 for Shift cursor right
   lcdCommandDelay();                    // Wait

   lcdDelay_ms( 1 );                     // Wait
}

int main(void)
{
	/* Inicializar la placa */
	boardConfig();
	/* Inicializar LCD: 16x2 caracteres de 5x8 px */
	mylcdInit( 16, 2, 5, 8 );
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
	lcdGoToXY( 3, 1 ); // Poner cursor en 1, 1
	lcdSendStringRaw( "Hello World!" );
	lcdGoToXY( 1, 2 ); //Siguiente linea
	delay(500);
	lcdSendStringRaw("Loading");
	delay(500);
	char i;
	for(i = 0; i<9;i++){
		lcdSendStringRaw(".");
		delay(200);
	}
	lcdClear();
}