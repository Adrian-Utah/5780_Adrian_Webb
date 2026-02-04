#ifndef __MAIN_H
#define __MAIN_H
#include <stm32f0xx_hal.h>
#include <stm32f072xb.h>

#ifdef __cplusplus
extern "C" {
#endif

void AL_RCC_GPIOC_CLK_Enable() ;

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init) ;

void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

void Error_Handler(void);

#ifdef __cplusplus
}

#endif



#endif /* __MAIN_H */
