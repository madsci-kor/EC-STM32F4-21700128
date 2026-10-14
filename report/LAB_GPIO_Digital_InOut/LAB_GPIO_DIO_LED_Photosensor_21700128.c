/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Yeonhu Kim
Created          : 05-03-2021
Modified         : 14-09-2026
Language/ver     : C++ in VS Code

Description      : Digital control of an LED (LED0) based on photosensor input state using STM32F4.
/----------------------------------------------------------------*/

#include "ecRCC2.h"
#include "ecGPIO2.h"

#define LED0 PB_12
#define PhotoSensor PA_0

// Initialiization 
void setup(void) {
	RCC_HSI_init();
	// initialize the photosensor pin as an input:
	GPIO_init(PhotoSensor, INPUT);  
	GPIO_pupd(PhotoSensor, 01);
	// initialize the LED pin as an output:
	GPIO_init(LED0, OUTPUT);
	GPIO_pupd(LED0, 01);
	GPIO_otype(LED0, 1);
	GPIO_ospeed(LED0, 01);
}
	
int main(void) { 
 	setup();
	int photoSensorState=0;
	
	while(1){
		// check if the photosensor is triggered. Turn LED on/off accordingly:
		photoSensorState = GPIO_read(PhotoSensor);
		if(photoSensorState)	GPIO_write(LED0, LOW);
		else 		GPIO_write(LED0, HIGH);
		delay_ms_HSI(100);             					// delay 100 ms
	}
}