#include "MKL46Z4.h" 

#include "mpu.h"
#include "lcd.h"

int main(){
	uint16_t i = 0;
	uint16_t z;
	I2C_Init(I2C1);
	slcdInitialize();

	Init();
	while(1){
		slcdDisplay(readX(),16);
		
	}
}
