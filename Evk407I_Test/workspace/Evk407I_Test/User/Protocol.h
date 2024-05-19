/*
 * Protocol.h
 *
 *  Created on: May 5, 2024
 *      Author: machi
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdint.h>
#include "datatype_define.h"
#include "utils.h"

#define CURVES_CH1 0x01
#define CURVES_CH2 0x02
#define CURVES_CH3 0x03
#define CURVES_CH4 0x04
#define CURVES_CH5 0x05


/* command (lower computer -> upper computer) */
#define CMD_SEND_TARGET   0x01 // Send the target value of the upper computer channel
#define CMD_SEND_CH       0x02 // Send channel actual value
#define CMD_SEND_P_I_D    0x03 // Send PID value (synchronize the value displayed by the host computer)
#define CMD_SEND_START    0x04 // Send the start command (synchronize the button state of the host computer)
#define CMD_SEND_STOP     0x05 // Send stop command (synchronize the button state of the host computer)
#define CMD_SEND_PERIOD   0x06 // Send period (synchronize the value displayed by the host computer)

/* command (upper computer -> lower computer) */
#define CMD_SET_P_I_D     0x10 // Set PID value
#define CMD_SET_TARGET    0x11 // set target value
#define CMD_START         0x12 // start command
#define CMD_STOP          0x13 // stop command
#define CMD_RESET         0x14 // reset command
#define CMD_SET_PERIOD    0x15 // set period


/* empty instruction */
#define CMD_NONE      0xFF // empty instruction

/**************************************************** ***********************************************
Protocol Data Example

1. Issue a target value of 55:
|----Header--| Ch |---Pkt Len--|Cmd |-Parameter-|Veri|
|0  1  2  3  | 4  | 5  6  7  8 | 9  |10 11 12 13| 14 | <- index
|53 5A 48 59 | 01 | 0F 00 00 00| 11 |37 00 00 00| A6 | <- protocol frame number


2. Issue PID (P=1 I=2 D=3):
|---Header---|-Ch-|---Pkt Len--|Cmd |-----P-----|-----I-----|-----D-----|Chk |
|0  1  2  3  | 4  | 5  6  7  8 | 9  |10 11 12 13|14 15 15 17|18 19 20 21| 22 | <- index
|53 5A 48 59 | 01 | 17 00 00 00| 10 |00 00 80 3F|00 00 00 40|00 00 40 40| F5 | <- number of protocol frames

***************************************************** *************************************************/

#define FRAME_HEADER 0x59485A53 // frame header

#define GUI_PKT_START   0xAA55
#define GUI_CMD_SEND    0xC1

/* Data header structure */
typedef struct tagPacketHead
{
   uint32_t head; // Baotou
   uint8_t ch;    // channel
   uint32_t len;  // packet length
   uint8_t cmd;   // command
}packet_head_t;

void set_computer_value(uint8_t cmd, uint8_t ch, void *data, uint8_t num);

//========================================================================

//rpm data
typedef struct tagSTATE_INFO {
  WORD_t rpm;
  WORD_t temp;
  WORD_t hum;
  uint8_t pg[2];
} STATEINFO_t;



//////////////////////////////////////////////////
// GUI Packet
typedef struct tagGUIPACKET {
  WORD_t    pa;         //Pre-amble
  uint8_t   len;        //Packet Length
  int8_t    cmd;        //Command
  WORD_t    rpm;        //Fan speed(rpm)
  WORD_t    temp;       //Fan speed(degree C)
  WORD_t    hum;        //Fan speed(%)
  int8_t    pg[2];      //PDU Power Good state
  WORD_t    checksum;   //
} GUIPACKET_t;

extern GUIPACKET_t guipacket;
extern STATEINFO_t stateinfo;

extern void     GUI_InitPacket(void);
extern void     GUI_InitStateInfo(void);
extern uint8_t  GUI_GetPacketLen(void);
extern void     GUI_MakePacket(void);
extern void     GUI_SendPacket(void);



#endif /* PROTOCOL_H_ */
