/*
 * pid.c
 *
 *  Created on: May 11, 2024
 *      Author: orion
 */

#include "pid.h"

PID pid;


void PID_param_init()
{
  //float pid_temp[3];

  /* Initialization parameters */
  pid.target_val=0.0;
  pid.output_val=0.0;
  pid.err=0.0;
  pid.err_last=0.0;
  pid.integral=0.0;

  pid.Kp = 0.0;
  pid.Ki = 0.0;
  pid.Kd = 0.0;

  #if defined(PID_ASSISTANT_EN)
  pid_temp[0] = pid.Kp;
  pid_temp[1] = pid. Ki;
  pid_temp[2] = pid.Kd;
  set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3); // Send PID value to channel 1
  #endif
}

void set_pid_target(float target_val)
{
  pid.target_val = target_val; // set the current target value
}

float get_pid_target(void)
{
  return pid.target_val; // Set the current target value
}

void set_p_i_d(float p, float i, float d)
{
  pid.Kp = p; // set the proportional coefficient P
  pid.Ki = i; // set the integral coefficient I
  pid.Kd = d; // set the differential coefficient D
}

float PID_calculate(float actual_val)
{
  /* Calculate the error between the target value and the actual value*/
  pid.err = pid.target_val - actual_val;

  /*Integral items*/
  pid.integral += pid.err;

  /*PID algorithm implementation*/
  pid.output_val = pid.Kp * pid.err + pid.Ki * pid.integral + pid.Kd * (pid.err - pid.err_last);

  /* error transmission */
  pid.err_last = pid.err;

  /*Return current actual value*/
  return pid. output_val;
}
