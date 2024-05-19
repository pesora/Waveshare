/*
 * ustils.c
 *
 *  Created on: May 12, 2024
 *      Author: orion
 */

///////////////////////////////////////////////////

#include <math.h>
#include "utils.h"
#include "usart.h"

// Make two 8-bit into a 16-bit word
uint16_t make16(uint8_t *hbyte, uint8_t *lbyte) {
  uint16_t data16=0;
    data16 = (uint16_t)(*hbyte);
    data16 = data16 << 8;
    data16 |= (uint16_t)(*lbyte);
    return data16;
}

///////////////////////////////////////////////////
// Seperate 16-bit into two 8-bit
uint8_t make8(uint16_t word, uint8_t pos) {
  uint8_t byte;
    byte = (uint8_t)(word>>(8*pos) & 0x00FF);
    return byte;
}

///////////////////////////////////////////////////
double Rounding( double x, int digit )
{
    return ( (double)floor( (double)(x) * pow( (double)10, digit ) + 0.5f ) / pow( (double)10, digit ) );
}

// Uart Put char
void put_char(int8_t c)
{
  HAL_UART_Transmit(&huart3, (uint8_t*)&c, sizeof(c), 100);
}


// Uart Put word
void put_word(uint16_t word) {
  char hi = make8(word, 1);
  char lo = make8(word, 0);
  put_char(hi);
  put_char(lo);
}


