#include "audio_processing.h"

uint16_t buffer_input[I2S_BUF_SIZE*2];
int32_t buffer_merged[I2S_BUF_SIZE/4];  // 250 değer, 500 değil!

int micflag = 0;
volatile int current_led_level = 0;
static volatile bool datenVerarbeiten = false;  // Warmup için flag

extern "C" void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef* hi2s){
	if (!datenVerarbeiten) {
		return;  // Warmup - data'yı at
	}
	
	// Eski kodun yöntemi: merge + shift birlikte
	for(int i=0, j=0; i<I2S_BUF_SIZE; i+=4, j++){
		int32_t mergedValue = ((int32_t)buffer_input[i] << 16) | buffer_input[i+1];
		mergedValue = mergedValue >> 14;  // 18-bit sample
		buffer_merged[j] = mergedValue;
	}
	micflag = 1;
	audioProcessingLeft();
}

void audioProcessingLeft(){
	// Eski kodun yöntemi: her sample'ı işle
	for(int i=0; i < I2S_BUF_SIZE/4; i++){
		// Skalaya eskisi gibi (550 böl, 12 çıkar)
		int anzahl = abs(buffer_merged[i] / 550) - 12;
		if(anzahl < 0) anzahl = 0;
		if(anzahl > 10) anzahl = 10;
		current_led_level = anzahl;
	}
}

extern "C" void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s){
	if (!datenVerarbeiten) {
		return;  // Warmup - data'yı at
	}
	
	// İkinci yarı: I2S_BUF_SIZE'dan başla
	for(int i=I2S_BUF_SIZE, j=0; i<I2S_BUF_SIZE*2; i+=4, j++){
		int32_t mergedValue = ((int32_t)buffer_input[i] << 16) | buffer_input[i+1];
		mergedValue = mergedValue >> 14;  // 18-bit sample
		buffer_merged[j] = mergedValue;
	}
	micflag = 2;
	audioProcessingRight();
}

void audioProcessingRight(){
	// Eski kodun yöntemi: her sample'ı işle
	for(int i=0; i < I2S_BUF_SIZE/4; i++){
		// Skalaya eskisi gibi (550 böl, 12 çıkar)
		int anzahl = abs(buffer_merged[i] / 550) - 12;
		if(anzahl < 0) anzahl = 0;
		if(anzahl > 10) anzahl = 10;
		current_led_level = anzahl;
	}
}

// Warmup enable fonksiyonu
void AudioProcessing_Enable(bool enable) {
	datenVerarbeiten = enable;
}

