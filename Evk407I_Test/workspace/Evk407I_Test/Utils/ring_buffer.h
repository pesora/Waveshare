/*
 * ring_buffer.h
 *
 *  Created on: Apr 30, 2024
 *      Author: orion
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<stddef.h>
#include<stdint.h>

// buffer type
typedef struct{
    uint16_t size; 
    uint16_t write;
    uint16_t read;
    uint8_t *data;
} RingBuf_t;

extern uint8_t RB_Init(RingBuf_t *pRingBuf, uint16_t size);
extern void    RB_Clear(RingBuf_t *pRingBuf);
extern uint8_t RB_IsEmpty(RingBuf_t *pRingBuf);
extern uint8_t RB_IsFull(RingBuf_t *pRingBuf);
extern void    RB_Write(RingBuf_t *pRingBuf, uint8_t data);
extern uint8_t RB_Read(RingBuf_t *pRingBuf);
extern uint16_t RB_GetCount(RingBuf_t *pRingBuf);


#endif /* RING_BUFFER_H_ */
