# LAB: EXTI & SysTick(eval board)

##

**Date:** 2026-10-07

**Author/Partner:** Yeonhu Kim

**Demo Video:** Youtube link



### Introduction

In this lab, you are required to create two simple programs using interrupt:

(1) Display the number counting from 0 to 9 with Button Press

(2) Counting at a rate of 1 second

You must submit

* LAB Report (\*.md & \*.pdf)
* Zip source files(main\*.c, ecRCC2.h, ecGPIO2.h, ecSysTick2.c etc...).
  * Only the source files. Do not submit project files

#### Requirement

**Hardware**

* MCU
  * NUCLEO-F411RE
* Eval Board (JKIT)
* Actuator/Sensor/Others:

**Software**

* PlatformIO, CMSIS, EC\_HAL library

***

## Tutorial: Programming Tips

#### 1.Tutorial: Managing library header files

Read how to manage library header files for MCU register configurations. Apply it in your LAB.

"<https://ykkim.gitbook.io/ec/ec-course/tutorial/tutorial-library-header-files#ec-2024>"

#### 2.Tutorial: Custom Initialization

Instead of writing initial setting functions for each registers, you can call a user defined function e.g. `MCU_init()` for the commonly used default initialization. Follow the tutorial and apply it in your LAB.

"<https://ykkim.gitbook.io/ec/ec-course/tutorial/tutorial-custom-initialization>"
***

## Problem 0: STM-Arduino

"<https://ykkim.gitbook.io/ec/ec-course/tutorial/tutorial-arduino-stm32/tutorial-arduino-stm32-part1#external-interrupt>"

We are going to create a simple program that turns LED(LD2) on triggered by **External Interrupt** of user button(BT1) (on NUCLEO-64, not on JKIT)

[**attachInterrupt()**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

```c
attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
```

* `digitalPinToInterrupt(pin)`: translate the digital pin to the specific interrupt number.
* `ISR`: a function called whenever the interrupt occurs.
* `mode`: defines when the interrupt should be triggered. (LOW, CHANGE, RISING, FALLING)

#### Procedure

1. Create a new project under the directory `\repos\EC\lab\`
2. Open *Arduino IDE* and Create a new program named as ‘**TU\_arduino\_EXTI.ino**’.
3. Write the following code.
   * Compare this code with the polling method in [Lab: GPIO-STM-Arduino](https://ykkim.gitbook.io/ec/ec-course/lab/lab-gpio-digital-inout-eval#example-code)

```
Difference : GPIO LED button 코드의 경우 loop문 내에서 계속하여 btnstate를 확인하여 LED 출력을 결정한다. 이 경우 확인 사이에 발생한 짧은 입력을 놓칠 수 있다.
하지만 inturrupt 방식의 경우 버튼 입력이 생기는 순간 등록된 ISR을 실행한다. 따라서 버튼을 누르고 있는 동안 LED가 켜지고, 놓으면 꺼진다.

```

```c
// TU_arduino_EXTI.ino
const int btnPin = 3;
const int ledPin =  13; 

int btnState = HIGH;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(btnPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(btnPin), blink, CHANGE);
}

void loop() {
    // blank
}


void blink(){
    btnState = digitalRead(btnPin);

    if (btnState == HIGH)
        digitalWrite(ledPin, LOW);
    else 
        digitalWrite(ledPin, HIGH);
}
```
```c
// TU_arduino_GPIO_LED_button.ino
const int btnPin = 3;
const int ledPin = 13;

int btnState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  btnState = digitalRead(btnPin);

  if (btnState == HIGH) 
    digitalWrite(ledPin, LOW);
  
  else 
    digitalWrite(ledPin, HIGH);
  
}
```

> The user button pin is `PC13`, but this pin cannot be used in arduino. So, you should connect `PC13` to `pinName` `D3` by using a wire.

<figure><img src="https://ykkim.gitbook.io/~gitbook/image?url=https%3A%2F%2Fuser-images.githubusercontent.com%2F91526930%2F186584565-3dc47e19-e5c5-43a2-b4c4-d4de8916a2c8.png&#x26;width=300&#x26;dpr=4&#x26;quality=100&#x26;sign=ff32bff&#x26;sv=1" alt="" width="375"><figcaption></figcaption></figure>

4. Click on **upload** button.
5. Whenever the user button(BT1) is pressed (at fall), LED should be ON. When the button is released, the LED should be OFF.

***

## Prelab: EXTI Register Setting

Do the PreLAB: External Interrupt

* It is about creating `ecEXTI.*` library
* Fill-in the blanks in the given header files
* Submit the Prelab report

```c
void EXTI_init(PinName_t pinName, uint32_t trig_type, uint32_t priority);
void EXTI_enable(uint32_t pin);  // mask in IMR
void EXTI_disable(uint32_t pin);  // unmask in IMR
uint32_t  is_pending_EXTI(uint32_t pin);
void clear_pending_EXTI(uint32_t pin);
```

## Problem 1: Counter on 7-Segment display using EXTI

#### **Problem**

Create a code to display the counter-up from 0 to 9 and repeating.

* Count up at the rate of 1 sec.
  * Use `delay_ms()` in the main loop
* Pause the counting when SW2 is pressed
* Resets to zero when the push button is pressed: SW1
  * Must use External Interrupts for SW1, SW2

**\* Challenge : Extend the count-up number : 0 to 59**<br><br>  


#### **Procedure**  

1. Connect the evaluation board [(JKIT-NUCLEO) ](https://ykkim.gitbook.io/ec/ec-course/hardware/stm32f-evaluation-board#reference-manual)to the MCU.
2. Make sure that your library are in `EC\include\`.
   * **ecRCC2.h, ecRCC2.c**
   * **ecGPIO2.h, ecGPIO2.c**
   * **ecSysTick2.h, ecSysTick2.c**
   * **ecEXTI2.h, ecEXTI2.c**
   * **ecSTM32F4v2.h**
3. Create a new project under the directory `EC\lab\`

* Environment: “**LAB\_EXTI”.**
* Source File: “**LAB\_EXTI.c”**

4. You must modify the `platformio.ini` **,** to add new environment.
  
#### **Configuration**

Configure the MCU GPIO

| Function                           | Port - Pin                                                                                        | Configuration                                 |
| ---------------------------------- | ------------------------------------------------------------------------------------------------- | --------------------------------------------- |
| **Button (SW1) on JKIT**           | PD\_2                                                                                             | DIN, Pull-Up                                  |
| **Button (SW2) on JKIT**           | PA\_4                                                                                             | DIN, Pull-Up                                  |
| **7-Segment DOUT**                 | <p>PB\_0, PB\_1, PB\_2, PB\_3, PB\_4, PB\_5, PB\_6, PB\_7</p><p>('a'\~'g''dot', respectively)</p> | Push-Pull, No Pull-up-Pull-down, Medium Speed |
| **Selection of 7-Segment Display** | PA\_10 (FND\_0)                                                                                   | DOUT, Push-Pull,                              |



#### Code



```c
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : [ YOUR NAME GOES HERE !!!!!]
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


```


#### Results

Experiment images and results go here

> Show experiment images /results

[video link](https://youtube.com/shorts/3Avg3pJF0zY) :

https://youtube.com/shorts/3Avg3pJF0zY

#### Discussion

1. Analyze the result and explain any other necessary discussion.

> In this lab, I implemented a function that checks whether one second has passed using SysTick's msTicks, and alternated the two 7-segment displays to show the numbers from 00 to 59. Press SW1 to reset the count to 0 on the EXTI2 interrupt. The SW2 detects both pressing and releasing; it stops counting while the button is held, and increases after 1 second of release. By separating delay_ms(1), which is used for display updates, and msTicks, which determines the tick increment, the FND can be displayed repeatedly while counting at approximately 1-second intervals.

2. We can use two different methods to detect an external signal: polling and interrupt. What are the advantages and disadvantages of each approach?

> POLLING uses a method where the main loop repeatedly reads button inputs. The code flow is simple and it is easy to check the input state at desired times, but loops may miss small input changes while executing other tasks or long-delayed functions. Since the INTERRUPT executes a designated handler when a change in the button signal occurs, it can respond to button inputs even while the main loop is displaying the FND. On the other hand, the EXTI line, trigger edge, NVIC, and pending bits must be properly configured, and if the button contacts bounce, multiple interrupts may occur, so debouncing is required as needed.

3. What would happen if the EXTI interrupt handler does not clear the interrupt pending flag? Check with your code

> EXTI's pending bit records that an interrupt has occurred on that line. If this bit is not cleared in the handler, an interrupt request may remain even after processing ends, causing the same handler to be executed repeatedly. In this program, each repetition of the SW1 interrupt causes the count and the 1-second reference time to be continuously reset, and each repetition of the SW2 interrupt may interfere with the display and time measurement of the main loop. To verify, temporarily comment out a handler's clear_pending_EXTI() call and observe its behavior, then restore the call.

### Reference

```
https://ykkim.gitbook.io/ec/ec-course/lab/lab-gpio-digital-inout-eval#example-code
https://ykkim.gitbook.io/ec/ec-course/lab/lab-exti-and-systick-eval
```
