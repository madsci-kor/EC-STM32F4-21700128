/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Yeonhu Kim
Created          : 05-03-2021
Modified         : 14-09-2026
Language/ver     : C++ in VS Code

Description      : Sequential 4-LED shift control triggered by digital input (switch) using STM32F4.
/----------------------------------------------------------------*/

#include "ecRCC2.h"
#include "ecGPIO2.h"

#define LED0 PB_12
#define LED1 PB_13
#define LED2 PB_14
#define LED3 PB_15
#define SW2 PA_4

// Initialiization 
void setup(void) {
	RCC_HSI_init();
	// initialize the photosensor pin as an input:
	GPIO_init(SW2, INPUT);
	GPIO_pupd(SW2, 01);  
	// initialize the LED pin as an output:
	GPIO_init(LED0, OUTPUT);
	GPIO_pupd(LED0, 01);
	GPIO_otype(LED0, 1);
	GPIO_ospeed(LED0, 01);

	GPIO_init(LED1, OUTPUT);
	GPIO_pupd(LED1, 01);
	GPIO_otype(LED1, 1);
	GPIO_ospeed(LED1, 01);

	GPIO_init(LED2, OUTPUT);
	GPIO_pupd(LED2, 01);
	GPIO_otype(LED2, 1);
	GPIO_ospeed(LED2, 01);

	GPIO_init(LED3, OUTPUT);
	GPIO_pupd(LED3, 01);
	GPIO_otype(LED3, 1);
	GPIO_ospeed(LED3, 01);
}
	
int main(void) { 
 	setup();
	GPIO_write(LED0, HIGH);
	GPIO_write(LED1, LOW);
	GPIO_write(LED2, LOW);
	GPIO_write(LED3, LOW);
	
	while(1){
		if(GPIO_read(SW2) == LOW){
			if (GPIO_read_ODR(LED0) == HIGH){
				GPIO_write(LED0, LOW); 
				GPIO_write(LED1, HIGH);
			}
			else if (GPIO_read_ODR(LED1) == HIGH){
				GPIO_write(LED1, LOW); 
				GPIO_write(LED2, HIGH);
			}
			else if (GPIO_read_ODR(LED2) == HIGH){
				GPIO_write(LED2, LOW); 
				GPIO_write(LED3, HIGH);
			}
			else if (GPIO_read_ODR(LED3) == HIGH){
				GPIO_write(LED3, LOW); 
				GPIO_write(LED0, HIGH);
			}
			delay_ms_HSI(100); 
		}		
	}
}