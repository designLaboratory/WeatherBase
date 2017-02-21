#include "MKL46Z4.h"

#include "i2c.h"




void I2C_Init(I2C_Type* i2c)
{
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[0]  = PORT_PCR_MUX(6);         // Alternative function: 4 (I2C0_SDA)
  PORTE->PCR[1]  = PORT_PCR_MUX(6);         // Alternative function: 4 (I2C0_SCL)
  
	I2C1->F   = /*I2C_F_MULT(2) |*/ I2C_F_ICR(0x1F);
}

void I2C_Disable(I2C_Type* i2c){
  i2c->C1 &= ~I2C_C1_IICEN_MASK;
}

void I2C_DisableInt(I2C_Type* i2c){
  i2c->C1 &= ~I2C_C1_IICIE_MASK;
}

void I2C_Enable(I2C_Type* i2c){
  i2c->C1 |= I2C_C1_IICEN_MASK;
}

void I2C_EnableInt(I2C_Type* i2c){
  i2c->C1 |= I2C_C1_IICIE_MASK;
}

uint8_t I2C_ReadByte(I2C_Type* i2c, uint8_t ack){
  // Select receive mode
  i2c->C1 &= ~I2C_C1_TX_MASK;
  
//  // Prepare ACK/NACK bit if FACK == 0
//  if((i2c->SMB & I2C_SMB_FACK_MASK) == 0)
//    i2c->C1 = (ack == I2C_NACK) ? i2c->C1 | I2C_C1_TXAK_MASK : i2c->C1 & ~I2C_C1_TXAK_MASK;
//  
  // Clear IICIF flag
  i2c->S |= I2C_S_IICIF_MASK;
  
  // Initiate data transfer
  (void)i2c->D;
  // Wait for transfer completion
  while((i2c->S & I2C_S_IICIF_MASK) == 0);
//  
//  // Send ACK/NACK bit if FACK == 1
//  if((i2c->SMB & I2C_SMB_FACK_MASK) != 0)
//    i2c->C1 = (ack == I2C_NACK) ? i2c->C1 | I2C_C1_TXAK_MASK : i2c->C1 & ~I2C_C1_TXAK_MASK;
//  
  // Select transmit mode - to omit next read of data byte
  i2c->C1 |= I2C_C1_TX_MASK;
  
  // Return received data
  return i2c->D;
}

void I2C_Restart(I2C_Type* i2c){
  i2c->C1 |= I2C_C1_RSTA_MASK;
}

void I2C_Start(I2C_Type* i2c){
  i2c->C1 |= I2C_C1_MST_MASK;
}

void I2C_Stop(I2C_Type * i2c){
  // Clear STOPF flag
  i2c->FLT |= I2C_FLT_STOPF_MASK;
  
  // Write STOP bit
  i2c->C1 &= ~I2C_C1_MST_MASK;
  // Wait until STOP bit is send
  while((i2c->FLT & I2C_FLT_STOPF_MASK) == 0){
    i2c->C1 &= ~I2C_C1_MST_MASK;
  }
}

void I2C_ack(I2C_Type *I2C)
{
	I2C->C1 &= ~I2C_C1_TXAK_MASK;				//  ACK do rozpoznania trybu
}

void I2C_nack(I2C_Type *I2C)
{
	I2C->C1 |= I2C_C1_TXAK_MASK;					// NACK do rozpoznania trybu
}

void I2C_WriteByte(I2C_Type* i2c, uint8_t data){
  // Select transmit mode 
	i2c->C1 |= I2C_C1_TX_MASK;
  
  // Clear IICIF flag
  i2c->S |= I2C_S_IICIF_MASK;
  
  // Initiate data transfer
  i2c->D = data;
  // Wait for transfer completion
  while((i2c->S & I2C_S_IICIF_MASK) == 0);   
	// Return received ACK bit
//  return ((i2c->S & I2C_S_RXAK_MASK) == I2C_S_RXAK_MASK ? I2C_NACK : I2C_ACK);
}

void sendACK(I2C_Type* i2c) // default i2c send ACK when TXAK is cleared, this function only clear TXAK
{
	i2c->C1 &= ~I2C_C1_TXAK_MASK;
}
	
void sendNACK(I2C_Type* i2c)
{
	i2c->C1 |= I2C_C1_TXAK_MASK;
}



volatile uint32_t msTicks;	
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;	// Zwieksz wartosc zmiennej msTicks wykorzystywanej w funkcji Delay()
}
 
/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 us)
 *------------------------------------------------------------------------------*/
void Delay_us(uint32_t dlyTicks) {
  uint32_t curTicks;
 
  curTicks = msTicks;												// Zachowaj aktualna wartosc zmiennej
  while ((msTicks - curTicks) < dlyTicks);  // Czekaj dopoki roznica aktualnej i
                                            // zachowanej wartosci jest mniejsza od
                                            // wartosci zmiennej dlyTicks
}
 
/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
void Delay_ms(uint32_t dlyTicks){
  do{
    Delay_us(1000);
  }
  while(--dlyTicks);
}
