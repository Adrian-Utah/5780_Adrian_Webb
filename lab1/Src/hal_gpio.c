#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f072xb.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    GPIOx->MODER |= (1 << 14) | (1 << 12);
    GPIOx->OTYPER &= ~(1<<6);
    GPIOx->OTYPER &= ~(1<<7);

    GPIOx->OSPEEDR &= ~(1<<12);
    GPIOx->OSPEEDR &= ~(1<<13);
    GPIOx->OSPEEDR &= ~(1<<14);
    GPIOx->OSPEEDR &= ~(1<<15);
    GPIOx->OSPEEDR &= ~(1<<1);

    GPIOx->PUPDR &= ~(1<<12);
    GPIOx->PUPDR &= ~(1<<13);
    GPIOx->PUPDR &= ~(1<<14);
    GPIOx->PUPDR &= ~(1<<15);
    GPIOx->PUPDR |= (1<<1);
    GPIOx->OSPEEDR &= ~(1<<0);
}


/*
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/

/*
GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return -1;
}
*/


void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    GPIOx->BSRR = GPIO_Pin;
}



void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint16_t odr = GPIOx->ODR;

  /* Set selected pins that were at low level, and reset ones that were high */
  GPIOx->BSRR = ((odr & GPIO_Pin) << 16U) | (~odr & GPIO_Pin);
}

