#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f072xb.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    GPIOx->MODER &= ~(1<<15);
    GPIOx->MODER |= (1 << 14); 
    GPIOx->MODER &= ~(1<<13);
    GPIOx->MODER |= (1 << 12);
    
    GPIOA->MODER &= ~(1<<0);
    GPIOA->MODER &= ~(1<<1);

    GPIOx->OTYPER &= ~(1<<6);
    GPIOx->OTYPER &= ~(1<<7);

    GPIOx->OSPEEDR &= ~(1<<12);
    GPIOx->OSPEEDR &= ~(1<<13);
    GPIOx->OSPEEDR &= ~(1<<14);
    GPIOx->OSPEEDR &= ~(1<<15);
    GPIOx->OSPEEDR &= ~(1<<1);
    GPIOx->OSPEEDR &= ~(1<<0);

    GPIOx->PUPDR &= ~(1<<12);
    GPIOx->PUPDR &= ~(1<<13);
    GPIOx->PUPDR &= ~(1<<14);
    GPIOx->PUPDR &= ~(1<<15);
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
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

}
