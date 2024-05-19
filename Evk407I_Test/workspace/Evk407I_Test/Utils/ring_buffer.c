/*
* ring_buffer.c
*
*  Created on: Apr 30, 2024
*      Author: orion
*/

#include "../Utils/ring_buffer.h"


uint8_t RB_Init(RingBuf_t *pRingBuf, uint16_t size)
{
  if(size & (size-1))
    return 1;

  pRingBuf->size = size;
  pRingBuf->write= 0;
  pRingBuf->read= 0;
  pRingBuf->data = malloc(size);
  assert(pRingBuf->data);

  return 0;
}

void RB_Clear(RingBuf_t *pRingBuf)
{
  pRingBuf->write= 0;
  pRingBuf->read= 0;
  memset(pRingBuf->data, 0, pRingBuf->size);
}

uint8_t RB_IsEmpty(RingBuf_t *pRingBuf)
{
  return (pRingBuf->read == pRingBuf->write);
}

uint8_t RB_IsFull(RingBuf_t *pRingBuf)
{
  return ((pRingBuf->size-1) & pRingBuf->read) == ((pRingBuf->size-1) & (pRingBuf->write+1));
}

void RB_Write(RingBuf_t *pRingBuf, uint8_t data)
{
  if(RB_IsFull(pRingBuf))
    return;

  pRingBuf->data[pRingBuf->write] = data;
  pRingBuf->write = (pRingBuf->size-1) & (pRingBuf->write+1);
}

uint8_t RB_Read(RingBuf_t *pRingBuf)
{
  uint8_t val = pRingBuf->data[pRingBuf->read];
  pRingBuf->read = (pRingBuf->size-1) & (pRingBuf->read+1);
  return val;
}

uint16_t RB_GetCount(RingBuf_t *pRingBuf)
{
  return ((pRingBuf->size-1) & (pRingBuf->write - pRingBuf->read));
}
