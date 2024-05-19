/*
 * utils.h
 *
 *  Created on: May 12, 2024
 *      Author: orion
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>


extern uint16_t make16(uint8_t *hbyte, uint8_t *lbyte);
extern uint8_t make8(uint16_t word, uint8_t pos);
extern double Rounding( double x, int digit );

extern void put_char(int8_t c);
extern void put_word(uint16_t word);


#endif /* UTILS_H_ */