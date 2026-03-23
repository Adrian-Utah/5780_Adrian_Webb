#include <main.h>
#include <stm32f0xx_hal.h>
#include <support.h>

void SystemClock_Config(void);

const uint8_t sine_wave[32] = {
    128, 152, 176, 198, 218, 234, 245, 253, 
    255, 253, 245, 234, 218, 198, 176, 152, 
    128, 103,  79,  57,  37,  21,  10,   2,   
      0,   2,  10,  21,  37,  57,  79, 103
};
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  volatile char mode;
  mode = 1;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  clockA();
  GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW,GPIO_NOPULL};
  Init(GPIOC,&initStr);
  writep(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
  writep(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
  writep(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
  writep(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);

  togglep(GPIOC, GPIO_PIN_6);
  togglep(GPIOC, GPIO_PIN_7);
  togglep(GPIOC, GPIO_PIN_8);
  togglep(GPIOC, GPIO_PIN_9);


  if(mode == 0){
    GPIOA->MODER |= (3U << 2);
    GPIOA->PUPDR &= ~(3U << 2);
    ADC1->CFGR1 &= ~ADC_CFGR1_RES; 
    ADC1->CFGR1 |= ADC_CFGR1_RES_1;

    ADC1->CFGR1 |= ADC_CFGR1_CONT;
    ADC1->CHSELR = ADC_CHSELR_CHSEL1;

    if ((ADC1->CR & ADC_CR_ADEN) != 0) {
          ADC1->CR |= ADC_CR_ADDIS;
    }

    while ((ADC1->CR & ADC_CR_ADEN) != 0);

    ADC1->CR |= ADC_CR_ADCAL;
    while ((ADC1->CR & ADC_CR_ADCAL) != 0);

    ADC1->ISR |= ADC_ISR_ADRDY;
    ADC1->CR |= ADC_CR_ADEN;
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);

    ADC1->CR |= ADC_CR_ADSTART;
  }
  if(mode==1){
    GPIOA->MODER |= (3U << 8);
    GPIOA->PUPDR &= ~(3U << 8);
    DAC->CR |= DAC_CR_TEN1;
    DAC->CR |= DAC_CR_TSEL1;
    DAC->CR |= DAC_CR_EN1;
  }
  uint8_t index = 0;
  while (1)
  {

    if(mode == 0){
    uint8_t val = ADC1->DR;

      if (val > 51) { 
        writep(GPIOC, GPIO_PIN_6, 1);
      }
      else {
        writep(GPIOC, GPIO_PIN_6, 0);
      }
      if (val > 102){ 
        writep(GPIOC, GPIO_PIN_8, 1);
      }
      else{ 
        writep(GPIOC, GPIO_PIN_8, 0);
      }
      if (val > 153) {
        writep(GPIOC, GPIO_PIN_7, 1);
      }  
      else {
        writep(GPIOC, GPIO_PIN_7, 0);
      }
      if (val > 204) {
        writep(GPIOC, GPIO_PIN_9, 1);
      }  
      else{
        writep(GPIOC, GPIO_PIN_9, 0);
      }
    }
    if(mode == 1){
      DAC->DHR8R1 = sine_wave[index];
      DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
      index = (index + 1) % 32;
      HAL_Delay(1);
    }

  }
  return -1;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add their own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add their own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
