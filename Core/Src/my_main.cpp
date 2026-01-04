/*
 * my_main.cpp
 *
 *  Created on: Dec 30, 2025
 *      Author: bash
 */
#include "my_main.h"
#include "main.h"
#include "audio_processing.h"
#include <stdio.h>
#include <cmath>

extern const int I2S_BUF_SIZE = 1000;
extern int micflag;
extern uint16_t buffer_input[I2S_BUF_SIZE*2];

extern UART_HandleTypeDef huart3;
extern  I2S_HandleTypeDef hi2s2;

// External buffer from audio_processing.cpp
extern int32_t buffer_merged[I2S_BUF_SIZE/2];

// PRINTF RETARGET - Redirect printf to UART3
extern "C" int _write(int file, char* ptr, int len) {
    (void)file;
    HAL_UART_Transmit(&huart3, reinterpret_cast<uint8_t*>(ptr), len, HAL_MAX_DELAY);
    return len;
}

void my_main(void){
	HAL_I2S_Receive_DMA(&hi2s2, &buffer_input[0], I2S_BUF_SIZE*2);
	while(1){
	}
}


