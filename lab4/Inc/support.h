#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#include <time.h>


void Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void clockA(void);
void tempfunc(void);
void writep(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void togglep(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void transmitA(volatile char* str);
char response(void);