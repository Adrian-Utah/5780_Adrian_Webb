
#include <main.h>
#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f072xb.h>
#include <assert.h>

void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
//HAL_Init();
//SystemClock_Config();
//HAL_RCC_GPIOC_CLK_Enable();


//GPIO_InitTypeDef initStr = {GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW,GPIO_NOPULL};
//HAL_GPIO_Init(GPIOC, &initStr);
//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);

GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW,GPIO_NOPULL};
//HAL_GPIO_Init(GPIOC, &initStr);
My_HAL_GPIO_Init(GPIOC,&initStr);
//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
//My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);

  uint32_t d = 0;
  GPIO_PinState s;
  uint32_t g = 0;
  uint32_t t = 0;
  uint32_t f = 1;
  My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
  while (1)
  {
    if(t){
      for(int i =0; i<40 ;i++){
        HAL_Delay(200);
        if(f){
        My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        f = 0;
        }
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7);
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7);
      }
      t=0;
    }

    //s = My_HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
    s = My_HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    d = (d<<1);
    if(s){
      d |= 0x01;
    }
    if(d == 0xFFFFFFFF){
      My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7);
      //g = !g;
      d=0;
    }
    if(d==0x0){

    }
    if(d == 0x7FFFFFFF){
      g=1;
    }


    /*
    if(g){
      HAL_Delay(200);
      if(f){
        My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        f = 0;
      }
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7);
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7);
    
  }
        */


    
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
