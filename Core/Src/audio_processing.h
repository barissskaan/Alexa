#ifndef AUDIO_PROCESSING_H
#define AUDIO_PROCESSING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <cmath>
#include "led_array.h"

#define I2S_BUF_SIZE 1000

void audioProcessingLeft();
void audioProcessingRight();

#ifdef __cplusplus
}
#endif

#endif /* AUDIO_PROCESSING_H */
