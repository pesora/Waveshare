/*
 * Protocol.c
 *
 *  Created on: May 5, 2024
 *      Author: machi
 */

#include "Protocol.h"
#include "usart.h"

  /* PID parameter initialization */
//  PID_param_init();

  #if defined(PID_ASSISTANT_EN)
  /*When initializing, send stop to synchronize the start button status of the host computer*/
  set_computer_value(SEND_STOP_CMD, CURVES_CH1, NULL, 0);

  /* get the default target value */
  target_speed = (int32_t)get_pid_target();
  /*Send target value to channel 1*/
  set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &target_speed, 1);
  #endif

uint8_t check_sum(uint8_t init, uint8_t *ptr, uint8_t len )
{
  /* checksum calculation result */
  uint8_t sum = init;

  while(len--)
  {
    sum += *ptr;/*Accumulate the value of each data in turn*/
    ptr++;
  }

  return sum;
}

void set_computer_value(uint8_t cmd, uint8_t ch, void *data, uint8_t num)
{
  static packet_head_t set_packet;

  uint8_t sum = 0;  // checksum
  num *= 1;         // 4 bytes for a parameter

  set_packet.head = FRAME_HEADER; // packet header 0x59485A53
  set_packet.ch = ch;             // set channel
  set_packet.len = 0x0B + num;    // packet length
  set_packet.cmd = cmd;           // set command

  sum = check_sum(0, (uint8_t *)&set_packet, sizeof(set_packet)); // Calculate the header checksum
  sum = check_sum(sum, (uint8_t *)data, num); // Calculate parameter checksum

  HAL_UART_Transmit(&huart3, (uint8_t *)&set_packet, sizeof(set_packet), 100); // send data header
  HAL_UART_Transmit(&huart3, (uint8_t *)data, num, 100);         // send parameters
  HAL_UART_Transmit(&huart3, (uint8_t *)&sum, sizeof(sum), 100); // send checksum
}

////////////////////////////////////////////////
GUIPACKET_t guipacket;
STATEINFO_t stateinfo;

uint8_t GUI_GetPacketLen(void)
{
  uint8_t len = 0;
  len += sizeof(WORD_t);    //pre-amble
  len += sizeof(uint8_t);   //packet length
  len += sizeof(int8_t);    //command
  len += sizeof(WORD_t);    //fan speed
  len += sizeof(WORD_t);    //temperature
  len += sizeof(WORD_t);    //humidity
  len += sizeof(guipacket.pg)/sizeof(int8_t);    //PG state
  len += sizeof(WORD_t);    //checksum
  return len;

}


void GUI_InitPacket(void)
{
  guipacket.pa.word = 0;
  guipacket.len = 0;
  guipacket.cmd = 0;
  guipacket.rpm.word = 0;
  guipacket.temp.word = 0;
  guipacket.hum.word = 0;
  guipacket.pg[0] = 0;
  guipacket.pg[1] = 0;
  guipacket.checksum.word = 0xFFFF;
}

void GUI_InitStateInfo(void)
{
  stateinfo.rpm.word = 0;
  stateinfo.temp.word = 0;
  stateinfo.hum.word = 0;
  stateinfo.pg[0] = 0;
  stateinfo.pg[1] = 0;
}

void GUI_MakePacket(void)
{
  guipacket.pa.word = GUI_PKT_START;
  guipacket.len = GUI_GetPacketLen();
  guipacket.cmd = GUI_CMD_SEND;
  guipacket.rpm.word = stateinfo.rpm.word;
  guipacket.temp.word = stateinfo.temp.word;
  guipacket.hum.word = stateinfo.hum.word;
  guipacket.pg[0] = stateinfo.pg[0];
  guipacket.pg[1] = stateinfo.pg[1];
  guipacket.checksum.word = 0xFFFF;

}


void GUI_SendPacket(void)
{
  put_word(guipacket.pa.word);
  put_char(guipacket.len);
  put_char(guipacket.cmd);
  put_word(guipacket.rpm.word);
  put_word(guipacket.temp.word);
  put_word(guipacket.hum.word);
  put_char(guipacket.pg[0]);
  put_char(guipacket.pg[1]);
  put_word(guipacket.checksum.word);

}


