#include <main.h>
#include <stm32f0xx_hal.h>
#include <support.h>


void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    int16_t x = 0;
    int16_t y = 0;
    int8_t xl = 0;
    int8_t yl = 0;
    int8_t xh = 0;
    int8_t yh = 0;
    int16_t thr = 1000;
    HAL_Init();
    SystemClock_Config();
    
    clockA();
    GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW,GPIO_NOPULL};
    Init(GPIOC,&initStr); 

    writep(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);
    HAL_Delay(100);
    togglep(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
    togglep(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);

    while (I2C2->ISR & I2C_ISR_BUSY);

    //togglep(GPIOC, GPIO_PIN_6);
    I2C2->CR2 = (0x69 << 1) | (2 << 16) | I2C_CR2_START; 
    while (!(I2C2->ISR & I2C_ISR_TXIS));
    I2C2->TXDR = 0x20;


    while (!(I2C2->ISR & I2C_ISR_TXIS));
    I2C2->TXDR = 0x0F; 

    while (!(I2C2->ISR & I2C_ISR_TC));
    I2C2->CR2 |= I2C_CR2_STOP;
    //part2
    /*
    while (!(I2C2->ISR & (I2C_ISR_TXIS | I2C_ISR_NACKF)));

    if (I2C2->ISR & I2C_ISR_NACKF) {
        togglep(GPIOC, GPIO_PIN_6);
        while(1);
    }
    I2C2->TXDR = 0x0F;

    while (!(I2C2->ISR & I2C_ISR_TC));


    I2C2->CR2 = (0x69 << 1) | (1 << 16) | I2C_CR2_RD_WRN | I2C_CR2_START;

    while (!(I2C2->ISR & (I2C_ISR_RXNE | I2C_ISR_NACKF)));

    if (I2C2->ISR & I2C_ISR_NACKF) {
        togglep(GPIOC, GPIO_PIN_6); 
        while(1);
    }

    uint8_t who_am_i = I2C2->RXDR;


    if (who_am_i == 0xD3) {
        writep(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
    } else {
        writep(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
    }

    I2C2->CR2 |= I2C_CR2_STOP;
    */
    
    while (1) {
      I2C2->CR2 = (0x69 << 1) | (1 << 16) | I2C_CR2_START;
      while (!(I2C2->ISR & I2C_ISR_TXIS));
      I2C2->TXDR = 0x28 | 0x80; 
      while (!(I2C2->ISR & I2C_ISR_TC));

      I2C2->CR2 = (0x69 << 1) | (4 << 16) | I2C_CR2_RD_WRN | I2C_CR2_START;
    
      while (!(I2C2->ISR & I2C_ISR_RXNE));
      xl = I2C2->RXDR;
      while (!(I2C2->ISR & I2C_ISR_RXNE));
      xh = I2C2->RXDR;
      while (!(I2C2->ISR & I2C_ISR_RXNE));
      yl = I2C2->RXDR;
      while (!(I2C2->ISR & I2C_ISR_RXNE));
      yh = I2C2->RXDR;

      x= (xl+(xh<<8));
      y= (yl+(yh<<8));
      if(x>thr){
        writep(GPIOC, GPIO_PIN_9, 1);
        writep(GPIOC, GPIO_PIN_8, 0);
      }else if(x<-thr){
        writep(GPIOC, GPIO_PIN_8, 1);
        writep(GPIOC, GPIO_PIN_9, 0);
      }
      if(y>thr){
        writep(GPIOC, GPIO_PIN_6, 1);
        writep(GPIOC, GPIO_PIN_7, 0);
      }else if(y<-thr){
        writep(GPIOC, GPIO_PIN_7, 1);
        writep(GPIOC, GPIO_PIN_6, 0);
      }
      HAL_Delay(100);
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
