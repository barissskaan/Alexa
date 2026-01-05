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

extern int micflag;
extern uint16_t buffer_input[2000];

extern UART_HandleTypeDef huart3;
extern  I2S_HandleTypeDef hi2s2;

// External buffer from audio_processing.cpp
extern int32_t buffer_merged[500];
extern volatile int current_led_level;

// PRINTF RETARGET - Redirect printf to UART3
extern "C" int _write(int file, char* ptr, int len) {
    (void)file;
    HAL_UART_Transmit(&huart3, reinterpret_cast<uint8_t*>(ptr), len, HAL_MAX_DELAY);
    return len;
}

void my_main(void){
	// DMA başlatma main.c'de yapılıyor
	while(1){
		// LED'i interrupt dışında yak (GPIO yavaş)
		led_func(current_led_level);
		HAL_Delay(50);  // 50ms bekle
	}
}


