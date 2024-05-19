/*
 * datatype_define.h
 *
 *  Created on: May 12, 2024
 *      Author: orion
 */

#ifndef DATATYPE_DEFINE_H_
#define DATATYPE_DEFINE_H_

#include <stdint.h>


/////////////////////////////////////////////////////
typedef union tagWORDtype
{
  uint16_t word;
  uint8_t byte[2];
  struct {
    uint8_t l;
    uint8_t h;
  };
} WORD_t;


typedef union tagDWORDtype
{
  uint32_t dword;
  uint8_t byte[4];
} DWORD_t;


#endif /* DATATYPE_DEFINE_H_ */
