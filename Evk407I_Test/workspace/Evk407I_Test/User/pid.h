/*
 * pid.h
 *
 *  Created on: May 11, 2024
 *      Author: orion
 */

#ifndef PID_H_
#define PID_H_

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
  float target_val;   //target value
  float err;          //deviation value
  float err_last;     //The last deviation value
  float Kp,Ki,Kd;     //Proportional, integral, differential coefficients
  float integral;     //integral value
  float output_val;   //output value
} PID;

extern void PID_param_init(void);
extern void set_pid_target(float target_val);
extern float get_pid_target(void);
extern void set_p_i_d(float p, float i, float d);
extern float PID_calculate(float actual_val);
//void time_period_fun(void);

#endif /* PID_H_ */
