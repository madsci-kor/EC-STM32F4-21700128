/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Yeonhu Kim
Created          : 05-03-2021
Modified         : 07-10-2026
Language/ver     : C++ in VS Code

Description      : LAB - 7segment counter from 00 to 59 using EXTI and SysTick.
                   SW1 resets the count; SW2 pauses it while pressed.
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"


#define SW1_PIN    PD_2			//EVAL board JKIT SW1
#define SW2_PIN    PA_4			//EVAL board JKIT SW2
PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4]={PA_10, PA_11, PC_4, PC_3};
// define a variable to hold the count value
volatile uint8_t count = 0;
volatile uint8_t paused = 0;
volatile uint32_t second_std = 0;

// Initialiization 
void setup(void)
{

    RCC_PLL_init();                 // System Clock = 84MHz
    SysTick_init();                 // SysTick Timer Initialization

    // Initialize switch inputs
    GPIO_init(SW1_PIN, INPUT);  // INPUT for EVAL board
    GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
    GPIO_pupd(SW1_PIN, 01);  // PULL-UP for EVAL board
    GPIO_pupd(SW2_PIN, 01);  // PULL-UP for EVAL board
    EXTI_init(SW1_PIN, FALL, 10);
    EXTI_init(SW2_PIN, BOTH, 10);

    // Intialize FND pins and Others for outputs
    FND_init(pinFND);
    FND_select_init(selectFND);    

    for (int i=0; i<8; i++){
        GPIO_otype(pinFND[i], 0);
        GPIO_pupd(pinFND[i], 00);
        GPIO_ospeed(pinFND[i], 01);
    }
    for (int i=0; i<4; i++){
        GPIO_otype(selectFND[i], 0);
        GPIO_pupd(selectFND[i], 00);
    }
    second_std = msTicks;
}


// MAIN  ----------------------------------------
int main(void) {
	setup();

	while (1){
        if (count>=60) count = 0;
        uint32_t now = msTicks;
        if (paused == 0 && (now - second_std) >= 1000){
            count++;
            second_std += 1000;
        }

        FND_select(0);
        FND_display(count % 10);
        delay_ms(1);

        // The second digit is the quotient of count divided by 10
        FND_select(1);
        FND_display(count / 10);
        delay_ms(1);
    }
}

void EXTI2_IRQHandler(void) {
	if (is_pending_EXTI(SW1_PIN)) {   
			count = 0; 
            second_std = msTicks;
			clear_pending_EXTI(SW1_PIN);
	}
    
}

void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
		if (GPIO_read(SW2_PIN) == LOW) {
            paused = 1U;
         } 
        else {
            paused = 0U;
         }
        second_std = msTicks;
		clear_pending_EXTI(SW2_PIN);
	}
}

