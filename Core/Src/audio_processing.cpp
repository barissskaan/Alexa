#include "audio_processing.h"
uint16_t buffer_input[4000];
uint32_t buffer_merged[1000];
int micflag = 0;


extern "C" void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef* hi2s){
	for(int i=0 ;i<2000;i+=4){
		uint32_t temp = (uint32_t)buffer_input[i]<<16;
		temp = temp | (uint32_t) buffer_input[i+1];
		buffer_merged[i/4] = temp;
	}
	micflag = 1;
	audioProcessingLeft();
}

void audioProcessingLeft(){
	int sum = 0;
	for(int i=0; i < 500; i++){
		sum += abs((int)buffer_merged[i]>>14);
	}
	led_func(sum/(500*780));
}

extern "C" void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s){
	for(int i=2000 ;i<4000;i+=4){
		uint32_t temp = (uint32_t)buffer_input[i]<<16;
		temp = temp | (uint32_t) buffer_input[i+1];
		buffer_merged[i/4] = temp;
		}
	micflag = 2;
	audioProcessingRight();
	}

void audioProcessingRight(){
	int sum = 0;
	for(int i=500; i < 1000; i++){
		sum += abs((int)buffer_merged[i]>>14);
	}
	led_func(sum/(500*780));
}

