#include "audio_processing.h"

uint16_t buffer_input[I2S_BUF_SIZE*2]; // 1000*2 16-bit values equivalent to 1000 32-bit values
int32_t buffer_merged[I2S_BUF_SIZE/2];  

int micflag = 0;

extern "C" void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef* hi2s){
	for(int i=0 ;i<1000;i+=4){
		uint32_t temp = (uint32_t)buffer_input[i]<<16;
		temp = temp | (uint32_t) buffer_input[i+1];
		buffer_merged[i/4] = (int32_t) temp;
	}
	micflag = 1;
	audioProcessingLeft();
}

void audioProcessingLeft(){
	int32_t sum = 0;
	for(int i=0; i < 250; i++){
		int32_t sample = buffer_merged[i] >> 14;  // 18-bit'ten 4-bit'e düşür
		sum += abs(sample);
	}
	// sum max ~2000, LED'ler için 10'a normalize et
	int led_count = sum / 200;
	if(led_count > 10) led_count = 10;
	if(led_count < 0) led_count = 0;
	led_func(led_count);
}

extern "C" void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s){
	for(int i=1000 ;i<2000;i+=4){
		uint32_t temp = (uint32_t)buffer_input[i]<<16;
		temp = temp | (uint32_t) buffer_input[i+1];
		buffer_merged[i/4] = (int32_t) temp;
		}
	micflag = 2;
	audioProcessingRight();
	}

void audioProcessingRight(){
	int32_t sum = 0;
	for(int i=250; i < 500; i++){
		int32_t sample = buffer_merged[i] >> 14;  // 18-bit'ten 4-bit'e düşür
		sum += abs(sample);
	}
	// sum max ~2000, LED'ler için 10'a normalize et
	int led_count = sum / 200;
	if(led_count > 10) led_count = 10;
	if(led_count < 0) led_count = 0;
	led_func(led_count);
}

