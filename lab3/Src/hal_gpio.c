#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f072xb.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{

    GPIOx->MODER &= ~(1<<19);
    GPIOx->MODER |= (1 << 18); 
    GPIOx->MODER &= ~(1<<17);
    GPIOx->MODER |= (1 << 16);
    //GPIOx->MODER &= ~(1<<15);
    //GPIOx->MODER |= (1 << 14); 
    //GPIOx->MODER &= ~(1<<13);
    //GPIOx->MODER |= (1 << 12);
    GPIOC->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    GPIOC->MODER |= (GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);
    GPIOC->AFR[0] &= ~(0xF << (6 * 4));
    GPIOC->AFR[0] &= ~(0xF << (7 * 4));

    GPIOA->MODER &= ~(1<<0);
    GPIOA->MODER &= ~(1<<1);



    GPIOx->OTYPER &= ~(1<<6);
    GPIOx->OTYPER &= ~(1<<7);

    GPIOx->OSPEEDR &= ~(1<<12);
    GPIOx->OSPEEDR &= ~(1<<13);
    GPIOx->OSPEEDR &= ~(1<<14);
    GPIOx->OSPEEDR &= ~(1<<15);
    GPIOx->OSPEEDR &= ~(1<<16);
    GPIOx->OSPEEDR &= ~(1<<17);
    GPIOx->OSPEEDR &= ~(1<<18);
    GPIOx->OSPEEDR &= ~(1<<19);
    GPIOx->OSPEEDR &= ~(1<<1);
    GPIOx->OSPEEDR &= ~(1<<0);

    GPIOx->PUPDR &= ~(1<<12);
    GPIOx->PUPDR &= ~(1<<13);
    GPIOx->PUPDR &= ~(1<<14);
    GPIOx->PUPDR &= ~(1<<15);
    GPIOx->PUPDR &= ~(1<<16);
    GPIOx->PUPDR &= ~(1<<17);
    GPIOx->PUPDR &= ~(1<<18);
    GPIOx->PUPDR &= ~(1<<19);
    GPIOA->PUPDR |= (1<<1);
    GPIOA->PUPDR &= ~(1<<0);
}


/*
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/


GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_PinState bitstatus;
    if((GPIOx->IDR & GPIO_Pin) != 0U){
        bitstatus = 1;
    }else{
        bitstatus = 0;
    }
    return bitstatus;
}



void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if (PinState == GPIO_PIN_SET) {
        GPIOx->BSRR = (uint32_t)GPIO_Pin;
    } else {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
    }
}



void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint32_t odr = GPIOx->ODR;

    GPIOx->BSRR = ((odr & GPIO_Pin) << 16U) | (~odr & GPIO_Pin);
}

void HAL_RCC_GPIOC_CLK_Enable(){
    uint32_t borg = 10;
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;


    
    TIM2->PSC = 39;
    TIM2->ARR = 50000;
    TIM3->PSC = 9;
    TIM3->ARR = 1000;
    TIM2->DIER |= TIM_DIER_UIE;
    //TIM3->DIER |= TIM_DIER_UIE;


    TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
    TIM3->CCMR1 |= (0x7 << TIM_CCMR1_OC1M_Pos);
    TIM3->CCMR1 |= (0x6 << TIM_CCMR1_OC2M_Pos);
    TIM3->CCMR1 |= (TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);
    TIM3->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);
    GPIOC->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    GPIOC->MODER |= (GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);
    TIM3->CCR1 = borg;
    TIM3->CCR2 = borg;

    


    TIM3->CR1 |= TIM_CR1_CEN;


    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1 |= TIM_CR1_CEN;


}

void MY_HAL_inEn(){
    
    EXTI->IMR |= GPIO_PIN_0;
    EXTI -> RTSR |= GPIO_PIN_0;
    SYSCFG->EXTICR[0] = 0x0;
    NVIC_SetPriority(SysTick_IRQn,2);
    NVIC_EnableIRQ(EXTI0_1_IRQn);
    NVIC_SetPriority(EXTI0_1_IRQn,1);
}
