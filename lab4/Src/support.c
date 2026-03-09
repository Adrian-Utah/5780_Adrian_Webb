#include <stdint.h>
#include <stm32f072xb.h>
#include <stm32f0xx_hal.h>

void tempfunc() {}
void clockA() {
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
}
void Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init) {
    GPIOB->MODER |= GPIO_MODER_MODER10_1;
    GPIOB->MODER |= GPIO_MODER_MODER11_1;
    GPIOB->MODER &= ~GPIO_MODER_MODER10_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER11_0;

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

    USART3->BRR = 0x45;

    GPIOB->AFR[1] &= ~((0xF << 8) | (0xF << 12));
    GPIOB->AFR[1] |=  ((4 << 8) | (4 << 12));

    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;
    USART3->CR1 |= USART_CR1_UE;
}

void writep(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){
    if (PinState == GPIO_PIN_SET) {
        GPIOx->BSRR = (uint32_t)GPIO_Pin;
    } else {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
    }
}

void togglep(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
    uint32_t odr = GPIOx->ODR;
    GPIOx->BSRR = ((odr & GPIO_Pin) << 16U) | (~odr & GPIO_Pin);
}

void transmitA(volatile char* str){
    while(*str){
    while(!(USART3->ISR & USART_ISR_TXE));
    USART3->TDR  = *str++;
  }

}
char response(){
    while (!(USART3->ISR & USART_ISR_RXNE));
    return (char)(USART3->RDR);
}