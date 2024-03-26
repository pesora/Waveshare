#ifndef __TS_I2C_H_
#define __TS_I2C_H_

#include "stm32f4xx_hal.h"

#define SDA_CLK()    	  __GPIOB_CLK_ENABLE();
#define SDA_GPIO_PORT   GPIOB
#define SDA_GPIO_PIN    GPIO_PIN_7

#define SCL_CLK()    	  __GPIOB_CLK_ENABLE();
#define SCL_GPIO_PORT   GPIOB
#define SCL_GPIO_PIN    GPIO_PIN_6

#define SET_SDA()     HAL_GPIO_WritePin(SDA_GPIO_PORT,SDA_GPIO_PIN,GPIO_PIN_SET)    
#define CLR_SDA()     HAL_GPIO_WritePin(SDA_GPIO_PORT,SDA_GPIO_PIN,GPIO_PIN_RESET)  

#define SET_CLK()     HAL_GPIO_WritePin(SCL_GPIO_PORT,SCL_GPIO_PIN,GPIO_PIN_SET)    
#define CLR_CLK()     HAL_GPIO_WritePin(SCL_GPIO_PORT,SCL_GPIO_PIN,GPIO_PIN_RESET)

#define READ_SDA()      HAL_GPIO_ReadPin(SDA_GPIO_PORT,SDA_GPIO_PIN)



void I2C_Init(void);		 
void I2C_Start(void);				
void I2C_Stop(void);	  			
void I2C_Send_Byte(uint8_t txd);		
uint8_t I2C_Read_Byte(uint8_t ack);	
uint8_t I2C_Wait_Ack(void); 				
void TS_Ack(void);					
void TS_NAck(void);				
void I2C_ReadReg(uint8_t I2c_Addr,uint8_t reg,uint8_t *buf,uint8_t len);
uint8_t I2C_WriteReg(uint8_t I2c_Addr,uint8_t reg,uint8_t *buf,uint8_t len);


#endif /*__CAP_I2C_H_*/
