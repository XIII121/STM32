#ifndef _LIGHTSENSOR_H_
#define _LIGHTSENSOR_H_

#include "stm32f10x.h"
void LightSensor_Inint(void);

uint8_t LightSensor_Get(void);


#endif
