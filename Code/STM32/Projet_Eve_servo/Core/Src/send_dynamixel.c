/*
 * send_dynamixel.c
 *
 *  Created on: Nov 22, 2023
 *      Author: Lucas
 */
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>


#include "stm32h7xx.h"

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;


unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size)
{
    unsigned short i, j;
    unsigned short crc_table[256] = {
        0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
        0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
        0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
        0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
        0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
        0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
        0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
        0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
        0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
        0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
        0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
        0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
        0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
        0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
        0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
        0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
        0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
        0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
        0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
        0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
        0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
        0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
        0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
        0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
        0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
        0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
        0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
        0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
        0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
        0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
        0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
        0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
    };

    for(j = 0; j < data_blk_size; j++)
    {
        i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
        crc_accum = (crc_accum << 8) ^ crc_table[i];
    }

    return crc_accum;
}
void send_dynamixel(uint8_t instruction[], size_t array_size){
	  uint8_t instruction_sent[array_size];
	  memcpy(instruction_sent, instruction, array_size);
	  unsigned short crc = update_crc(0, instruction_sent, array_size-2);//initializing the message with 4 crc bytes at 0 so we take array_size-2 to not count them in the CRC calculation
	  unsigned char crc_l = (unsigned char)(crc & 0x00FF);
	  unsigned char crc_h = (unsigned char)((crc >> 8) & 0x00FF);
	  instruction_sent[array_size -2]=crc_l;
	  instruction_sent[array_size - 1]=crc_h;
	  //while(!__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TXE));
	  HAL_UART_Transmit(&huart4,instruction_sent,sizeof(instruction_sent),10);
}

// Status 1 : Led ON, status 0 : Led OFF
void ToggleLed(int status){
	  uint8_t Dynamixel_LED_ON_XL430[] = {0xFF, 0xFF, 0xFD, 0x00,/*id*/ 0x01, /*length*/0x06, 0x00,/*type instruction, ici write*/0x03
			  /*débutparam, address 65:*/ ,0x41,0x00
			  /*value in the address*/,0x01
	  	  	  /*on calcul le CRC après */,0x00,0x00};

	  uint8_t Dynamixel_LED_OFF_XL430[] = {0xFF, 0xFF, 0xFD, 0x00,/*id*/ 0x01, /*length*/0x06, 0x00,/*type instruction, ici write*/0x03
			  /*débutparam, address 65:*/ ,0x41,0x00
			  /*value in the address*/,0x00
	  	  	  /*on calcul le CRC après */,0x00,0x00};
	  if(status == 1){
		  send_dynamixel(Dynamixel_LED_ON_XL430, sizeof(Dynamixel_LED_ON_XL430));
	  }
	  if(status == 0){
	  		  send_dynamixel(Dynamixel_LED_OFF_XL430, sizeof(Dynamixel_LED_OFF_XL430));
	  	  }
}
// mode 1 : rotate mode, mode 0 : receive and transmit mode
void ToggleTorque(int mode){
	  /*autorise le moteur a tourner ( pas de transimission/récpetion possible dans ce mode*/
	    uint8_t Dynamixel_RotateMode_XL430[] = {0xFF, 0xFF, 0xFD, 0x00,/*id*/ 0x01, /*length*/0x06, 0x00,/*type instruction, ici write*/0x03
	     		  /*débutparam, address 64:*/ ,0x40,0x00
	     		  /*value in the address : 1*/,0x01
	       	  	  /*CRC*/				,0x00,0x00};

	    uint8_t Dynamixel_ComMode_XL430[] = {0xFF, 0xFF, 0xFD, 0x00,/*id*/ 0x01, /*length*/0x06, 0x00,/*type instruction, ici write*/0x03
	     		  /*débutparam, address 64:*/ ,0x40,0x00
	     		  /*value in the address : 1*/,0x00
	       	  	  /*CRC*/				,0x00,0x00};
	    if(mode == 1){
	    	send_dynamixel(Dynamixel_RotateMode_XL430, sizeof(Dynamixel_RotateMode_XL430));
	    }
	    if(mode == 0){
	    	send_dynamixel(Dynamixel_ComMode_XL430, sizeof(Dynamixel_ComMode_XL430));
	    	    }
}
/*value :
1 = velocity control,This mode controls velocity and ideal for wheel operation.,This mode is identical to the Wheel Mode(endless) from existing DYNAMIXEL.

3(default) = Position control mode, This mode controls position and identical to the Joint Mode.
			Operating position range is limited by Max Position Limit(48) and Min Position Limit(52).
			This mode is ideal for articulated robots that each joint rotates less than 360°.

 4 = This mode controls position and identical to Multi-turn Mode.
	512 turns are supported(-256[rev] ~ 256[rev]) and ideal for multi-turn wrists or conveyer systems or a system that requires an additional reduction gear.

*/
void SetOperatingMode(int mode){
	uint8_t Dynamixel_ChangePosition_XL430[] = {0xFF, 0xFF, 0xFD, 0x00,/*id*/ 0x01, /*length*/0x09, 0x00,/*type instruction, ici write*/0x03
	 		  /*débutparam, address 116:*/ ,0x74,0x00
	 		  /*value in the address : 2048*/,0x00,0x08,0x00,0x00
	   	  	  /*CRC*/				,0xCA,0x89};
}

//0.088 [deg/pulse]	1[rev] : 0 ~ 4,09

void RotateToPosition(float angleInDeg) {
    // Value range: 0 to 4095
    const int maxValue = 4095;

    // Adding security
    if (angleInDeg < 0) {
        angleInDeg = 0;
    } else if (angleInDeg > 360) {
        angleInDeg = 360;
    }

    // Convert degrees to the range [0, 360)
    while (angleInDeg >= 360.0) {
        angleInDeg -= 360.0;
    }

    // Convert degrees to the range [0, maxValue]
    int angleInInt = (int)round((angleInDeg / 360.0) * maxValue);

    // Convert to uint8_t array
    uint8_t HexAngle[2];
    HexAngle[0] = (uint8_t)((angleInInt >> 0) & 0xFF);
    HexAngle[1] = (uint8_t)((angleInInt >> 8) & 0xFF);


    // Now HexAngle contains the 12-bit representation of the angle //change position to 90,

    uint8_t Dynamixel_ChangePosition_XL430[] = {0xFF, 0xFF, 0xFD, 0x00,/*id*/ 0x01, /*length*/0x09, 0x00,/*type instruction, ici write*/0x03
    		  /*débutparam, address 116:*/ ,0x74,0x00
    		  /*value in the address :2048*/,0x00,0x08,0x00,0x00
    	  	  /*CRC*/				,0xCA,0x89};
}




void RotateToExtendedPosition(float angleInDeg){}

//refer to Drive
void DriveMode(){}
