#include "mpu.h"

int read(uint8_t RegisterAdress){
	
	uint8_t a;
  uint8_t b;
	
	
	I2C_Enable(I2C1);
	I2C_Start(I2C1);
	I2C_WriteByte(I2C1,0x68 << 1);
	I2C_WriteByte(I2C1,RegisterAdress);
	I2C_Restart(I2C1);
	I2C_WriteByte(I2C1, (0x68 << 1) +1);
	sendACK(I2C1);
	a = I2C_ReadByte(I2C1,a);
	sendNACK(I2C1);
	b = I2C_ReadByte(I2C1,b);
	I2C_Stop(I2C1);
	I2C_Disable(I2C1);
	return (a << 8)+ b;	
	
	
}

void setRegister(uint8_t Adress, uint8_t value)
{
	//I2C_Init(I2C1);
	I2C_Enable(I2C1);
	I2C_Start(I2C1);
	I2C_WriteByte(I2C1,0x68 << 1);
	I2C_WriteByte(I2C1,Adress);
	I2C_WriteByte(I2C1,value);
	I2C_Stop(I2C1);
	I2C_Disable(I2C1);

}


void Init()
{
	setRegister(0x6B,0x00);
}

uint16_t readZ()
{
	return read(0x3B);
}

uint16_t readX()
{
	return read(0x3F);
}


uint16_t readY()
{
	return read(0x3D);
}