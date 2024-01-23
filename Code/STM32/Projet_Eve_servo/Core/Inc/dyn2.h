/*
 * dyn2.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Lucas
 */

#ifndef INC_DYN2_H_
#define INC_DYN2_H_


#include "main.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include <stdint.h>

void dyn2_send(uint8_t* instruction);
void dyn2_led(int status);

void dyn2_rotate_positionPosition(float angleInDeg);


#endif /* INC_DYN2_H_ */
