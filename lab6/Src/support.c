#include <stdint.h>
#include <stm32f072xb.h>
#include <stm32f0xx_hal.h>

void tempfunc() {}
void clockA() {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    RCC->CR2 |= RCC_CR2_HSI14ON;
    while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0);
}
void Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init) {

    GPIOx->MODER &= ~(1<<19);
    GPIOx->MODER |= (1 << 18); 
    GPIOx->MODER &= ~(1<<17);
    GPIOx->MODER |= (1 << 16);
    GPIOx->MODER &= ~(1<<15);
    GPIOx->MODER |= (1 << 14); 
    GPIOx->MODER &= ~(1<<13);
    GPIOx->MODER |= (1 << 12);

    GPIOx->OSPEEDR &= ~(1<<12);
    GPIOx->OSPEEDR &= ~(1<<13);
    GPIOx->OSPEEDR &= ~(1<<14);
    GPIOx->OSPEEDR &= ~(1<<15);
    GPIOx->OSPEEDR &= ~(1<<16);
    GPIOx->OSPEEDR &= ~(1<<17);
    GPIOx->OSPEEDR &= ~(1<<18);
    GPIOx->OSPEEDR &= ~(1<<19);

    GPIOx->PUPDR &= ~(1<<12);
    GPIOx->PUPDR &= ~(1<<13);
    GPIOx->PUPDR &= ~(1<<14);
    GPIOx->PUPDR &= ~(1<<15);
    GPIOx->PUPDR &= ~(1<<16);
    GPIOx->PUPDR &= ~(1<<17);
    GPIOx->PUPDR &= ~(1<<18);
    GPIOx->PUPDR &= ~(1<<19);



}

void writep(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
  if (PinState == GPIO_PIN_SET) {
    GPIOx->BSRR = (uint32_t)GPIO_Pin;
  } else {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
  }
}

void togglep(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  uint32_t odr = GPIOx->ODR;
  GPIOx->BSRR = ((odr & GPIO_Pin) << 16U) | (~odr & GPIO_Pin);
}
