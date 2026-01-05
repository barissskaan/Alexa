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
extern I2S_HandleTypeDef hi2s2;

extern int32_t buffer_merged[250];  // 250, 500 değil!
extern volatile int current_led_level;

// Audio processing
void AudioProcessing_Enable(bool enable);

// PRINTF RETARGET - Redirect printf to UART3
extern "C" int _write(int file, char* ptr, int len) {
    (void)file;
    HAL_UART_Transmit(&huart3, reinterpret_cast<uint8_t*>(ptr), len, HAL_MAX_DELAY);
    return len;
}

void my_main(void){
	printf("\r\n>>> Mikrofon baslatiliyor...\r\n");
	
	// LED test
	led_func(0);
	
	// Warmup: 2 saniye bekle mikrofon için
	printf("[WARMUP] 2 saniye bekleniyor...\r\n");
	uint32_t warmupStart = HAL_GetTick();
	while (HAL_GetTick() - warmupStart < 2000) {
		// LED animasyon
		int pos = ((HAL_GetTick() / 100) % 20);
		if (pos >= 10) pos = 19 - pos;
		led_func(pos + 1);
	}
	led_func(0);
	
	// Data processing'i aktifleştir
	AudioProcessing_Enable(true);
	printf("[OK] Mikrofon hazir!\r\n\r\n");
	
	// Main loop
	while(1){
		// LED'i interrupt dışında yak (GPIO yavaş)
		led_func(current_led_level);
		HAL_Delay(50);  // 50ms bekle
	}
}


