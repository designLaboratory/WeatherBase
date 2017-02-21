#ifndef mpu_h
#define mpu_h


#include "MKL46Z4.h" 
#include "i2c.h"

int read(uint8_t);
void setRegister(uint8_t, uint8_t);
void Init(void);
uint16_t readZ();
uint16_t readX();


#endif
