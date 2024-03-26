#ifndef __UDA1380_H__
#define __UDA1380_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "i2c.h" 
#include "sai.h"

#define AUIDO_START_ADDRESS       58 /* Offset relative to audio file header size */

#define UDA1380_WRITE_ADDRESS     0x30
#define UDA1380_REG_EVALCLK	      0x00
#define UDA1380_REG_I2S		        0x01
#define UDA1380_REG_PWRCTRL	      0x02
#define UDA1380_REG_ANAMIX	      0x03
#define UDA1380_REG_HEADAMP	      0x04
#define UDA1380_REG_MSTRVOL	      0x10
#define UDA1380_REG_MIXVOL	      0x11
#define UDA1380_REG_MODEBBT	      0x12
#define UDA1380_REG_MSTRMUTE      0x13
#define UDA1380_REG_MIXSDO	      0x14
#define UDA1380_REG_DECVOL	      0x20
#define UDA1380_REG_PGA		        0x21
#define UDA1380_REG_ADC		        0x22
#define UDA1380_REG_AGC		        0x23

#define UDA1380_REG_L3		        0x7f
#define UDA1380_REG_HEADPHONE     0x18
#define UDA1380_REG_DEC		        0x28

uint8_t  UDA1380_Init(void);

#endif  // __UDA1380_H__







