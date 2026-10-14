/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Yeonhu Kim
Created          : 05-03-2021
Modified         : 22-09-2026
Language/ver     : C++ in VS Code

Description      : Two-digit decimal counter on 7-Segment (FND) incremented by switch input using STM32F4.
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4]={PA_10, PA_11, PC_4, PC_3};
#define SW2 PA_4

void setup(void){
    // Intialize System Clock
    RCC_HSI_init();    
    // initialize the switch as an input:
	GPIO_init(SW2, INPUT);
	GPIO_pupd(SW2, 01);  
    // Intialize FND pins and Others
    FND_init(pinFND);
    FND_select_init(selectFND);    
     // Intialize  Others
    for (int i=0; i<8; i++){
        GPIO_otype(pinFND[i], 0);
        GPIO_pupd(pinFND[i], 00);
        GPIO_ospeed(pinFND[i], 01);
    }
    for (int i=0; i<4; i++){
        GPIO_otype(selectFND[i], 0);
        GPIO_pupd(selectFND[i], 00);
    }
};

int main(void) {
    setup();
    // define a variable to hold the count value
    uint8_t count = 0;

    while (1)
    {
        // first digit
        FND_select(0);
        // The first digit is the remainder of count divided by 10
        FND_display(count % 10);
        delay_ms_HSI(1);

        // The second digit is the quotient of count divided by 10
        FND_select(1);
        FND_display(count / 10);
        delay_ms_HSI(1);

        if (GPIO_read(SW2) == 0)
        {
            count++;
            if (count >= 20){
                count = 0;
            }             
            delay_ms_HSI(100);
        }
    }
}