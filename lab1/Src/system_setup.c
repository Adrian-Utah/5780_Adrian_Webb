
#include <stm32f072xb.h>
#include <main.h>

void HAL_RCC_GPIOC_CLK_Enable(){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
}