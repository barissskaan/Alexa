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

extern const int I2S_BUF_SIZE;
extern int micflag;
extern uint16_t buffer_input[];

extern UART_HandleTypeDef huart3;
extern  I2S_HandleTypeDef hi2s2;

// External buffer from audio_processing.cpp
extern int32_t buffer_merged[];

// PRINTF RETARGET - Redirect printf to UART3
extern "C" int _write(int file, char* ptr, int len) {
    (void)file;
    HAL_UART_Transmit(&huart3, reinterpret_cast<uint8_t*>(ptr), len, HAL_MAX_DELAY);
    return len;
}

static int dma_started = 0;

void my_main(void){
	if(!dma_started) {
		HAL_I2S_Receive_DMA(&hi2s2, buffer_input, 2000);
		dma_started = 1;
	}
	while(1){
	}
}


