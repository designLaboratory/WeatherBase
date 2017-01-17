


#include  "MKL46Z4.h"
#include "LCD.h"
#include "I2C.h"
#include "ADC.h"
#include "i2cc.h"

int main(void){
	int temperature=0;
	uint8_t ack;
	
  SystemCoreClockUpdate();                        // Wywolanie tej funkcji spowoduje zapisanie
																									// wartosci czestotliwosci (w hercach)
                                                  // systemowego sygnalu taktujacego do zmiennej
                                                  // SystemCoreClock zadeklarowanej w pliku
                                                  // system_MKL25Z4.c
  SysTick_Config(SystemCoreClock/1000000);
	
  
	I2C_Init(I2C1);
	I2C_Enable(I2C1);
	I2C_Start(I2C1);
	I2C_WriteByte(I2C1,0xEE);
	I2C_WriteByte(I2C1,0xFF);
	I2C_WriteByte(I2C1, 0xF0);
	I2C_Stop(I2C1);
	Delay_ms(28);
	I2C_Start(I2C1);
	I2C_WriteByte(I2C1,0xEE);
	I2C_WriteByte(I2C1,0xED);
	I2C_Restart(I2C1);
	ack=I2C_WriteByte(I2C1,0xEF);
	//temperature=I2C_ReadByte(I2C1,ack);
	temperature=I2C_ReadByte(I2C1,ack);
	sLCD_init();
	sLCD_disp(temperature);
	while(1){
		
	};
	
	


	//ADC_inti();
	
 
		

  
 
  //SystemCoreClockUpdate();                        // Wywolanie tej funkcji spowoduje zapisanie
																									// wartosci czestotliwosci (w hercach)
                                                  // systemowego sygnalu taktujacego do zmiennej
                                                  // SystemCoreClock zadeklarowanej w pliku
                                                  // system_MKL25Z4.c
  //SysTick_Config(SystemCoreClock/1000000);        // Przekazywana funkcji wartosc okresla co ile
                                             // taktow zegara systemowego ma byc generowane
                                                      // przerwanie (w danym przypadku dla
                                                  // czestotliwosci 48 MHz bedzie to 1 us)
 
 
 
 // I2C1_Init();                                    // Konfiguracja linii we/wy i ukladu I2C1

// 
//  while(1){
//   // temperature = ReadTemperature();              // Odczyt wartosci calkowitej temperatury
//			sLCD_set(temperature,1);																						// Sklejenie tej wartosci i znakow 'oC'
// 
//                                 // Czyszczenie 2 wiersza
//                                  // Ustawienie pozycji: 2 wiersz, 1 kolumna
//                         // Wyslanie ciagu znakow
// 
//   // Delay_ms(1000);                               // Czekaj 1 s
//  }
}
