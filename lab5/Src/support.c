#include <stdint.h>
#include <stm32f072xb.h>
#include <stm32f0xx_hal.h>

void tempfunc() {}
void clockA() {
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;


  I2C2->TIMINGR &= ~(0xF0FFFFFF);
  I2C2->TIMINGR |= (1U << 28);
  I2C2->TIMINGR |= (0x4U << 20);
  I2C2->TIMINGR |= (0x2U << 16);
  I2C2->TIMINGR |= (0x0FU << 8);
  I2C2->TIMINGR |= (0x13U << 0);
}
void Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init) {
  GPIOB->MODER &= ~GPIO_MODER_MODER15;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR15;
  
  GPIOC->MODER &= ~GPIO_MODER_MODER0;
  GPIOC->MODER |= GPIO_MODER_MODER0_0;
  GPIOC->OTYPER &= ~GPIO_OTYPER_OT_0;
  
  GPIOB->MODER &= ~GPIO_MODER_MODER14;
  GPIOB->MODER |= GPIO_MODER_MODER14_0;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_14; 


  GPIOC->BSRR = GPIO_BSRR_BS_0;
  GPIOB->BSRR = GPIO_BSRR_BS_14;
  
  HAL_Delay(100);


  GPIOB->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER13);
  GPIOB->MODER |= (GPIO_MODER_MODER11_1 | GPIO_MODER_MODER13_1);


  GPIOB->OTYPER |= (GPIO_OTYPER_OT_11 | GPIO_OTYPER_OT_13);

  GPIOB->AFR[1] &= ~((0xFU << 12) | (0xFU << 20));
  GPIOB->AFR[1] |= (1U << 12);
  GPIOB->AFR[1] |= (5U << 20);

  GPIOx->MODER &= ~(1 << 19);
  GPIOx->MODER |= (1 << 18);
  GPIOx->MODER &= ~(1 << 17);
  GPIOx->MODER |= (1 << 16);
  GPIOx->MODER &= ~(1 << 15);
  GPIOx->MODER |= (1 << 14);
  GPIOx->MODER &= ~(1 << 13);
  GPIOx->MODER |= (1 << 12);

  GPIOx->OTYPER &= ~(1 << 6);
  GPIOx->OTYPER &= ~(1 << 7);
  GPIOx->OTYPER &= ~(1 << 9);
  GPIOx->OTYPER &= ~(1 << 8);

  GPIOx->OSPEEDR &= ~(1 << 12);
  GPIOx->OSPEEDR &= ~(1 << 13);
  GPIOx->OSPEEDR &= ~(1 << 14);
  GPIOx->OSPEEDR &= ~(1 << 15);
  GPIOx->OSPEEDR &= ~(1 << 16);
  GPIOx->OSPEEDR &= ~(1 << 17);
  GPIOx->OSPEEDR &= ~(1 << 18);
  GPIOx->OSPEEDR &= ~(1 << 19);

  GPIOx->PUPDR &= ~(1 << 12);
  GPIOx->PUPDR &= ~(1 << 13);
  GPIOx->PUPDR &= ~(1 << 14);
  GPIOx->PUPDR &= ~(1 << 15);
  GPIOx->PUPDR &= ~(1 << 16);
  GPIOx->PUPDR &= ~(1 << 17);
  GPIOx->PUPDR &= ~(1 << 18);
  GPIOx->PUPDR &= ~(1 << 19);

  I2C2->CR1 |= I2C_CR1_PE;
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