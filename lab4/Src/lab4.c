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
  /*
  volatile char* str= "I Need Orders\r\n";
  volatile char* pt = str;
  */
  char r;
  char g;
  char b;
  char o;

  char sb;

  char read;
  char read2;

  sb = 0;
  r=0;
  g=0;
  b=0;
  o=0;
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
  USART3->ICR |= (USART_ICR_ORECF | USART_ICR_FECF | USART_ICR_NCF);

  
  while (1)
  {
    if(!sb){
      transmitA("I Need Orders\r\n");
      sb = 1;
    }
    read = response();
    if(read == 'r'){
      transmitA("red, specification?\r\n");  
      togglep(GPIOC, GPIO_PIN_6);
      /*
      read2 = response();
      if(read2=='2'){
        togglep(GPIOC, GPIO_PIN_6);
        transmitA("red, toggle\r\n");
        g = !g;
      }else if(read2=='1'){
        if(!g){
          togglep(GPIOC, GPIO_PIN_6);
          g=1;
        }
        transmitA("red, on\r\n");
      }else if(read2=='0'){
        if(g){
          togglep(GPIOC, GPIO_PIN_6);
          g=0;
        }
        transmitA("red, off\r\n");
      }else{
        transmitA("ERROR input not valid\r\n");
      }
        */
      sb = 0;
    }else if(read == 'g') {
      transmitA("green, specification?\r\n");
      togglep(GPIOC, GPIO_PIN_9);
      /*
      read2 = response();
      if(read2=='2'){
        togglep(GPIOC, GPIO_PIN_9);
        transmitA("green, toggle\r\n");
        g = !g;
      }else if(read2=='1'){
        if(!g){
          togglep(GPIOC, GPIO_PIN_9);
          g=1;
        }
        transmitA("green, on\r\n");
      }else if(read2=='0'){
        if(g){
          togglep(GPIOC, GPIO_PIN_9);
          g=0;
        }
        transmitA("green, off\r\n");
      }else{
        transmitA("ERROR input not valid\r\n");
      }
        */
      sb = 0;
    }else if (read == 'b') {

      
      transmitA("blue, specification?\r\n");
      togglep(GPIOC, GPIO_PIN_7);
      /*
      read2 = response();
      if(read2=='2'){
        togglep(GPIOC, GPIO_PIN_7);
        transmitA("blue, toggle\r\n");
        b = !b;
      }else if(read2=='1'){
        if(!b){
          togglep(GPIOC, GPIO_PIN_7);
          b=1;
        }
        transmitA("blue, on\r\n");
      }else if(read2=='0'){
        if(b){
          togglep(GPIOC, GPIO_PIN_7);
          b=0;
        }
        transmitA("blue, off\r\n");
      }else{
        transmitA("ERROR input not valid\r\n");
      }
      */
      sb = 0;
    }else if (read == 'o') {
      transmitA("orange, specification?\r\n");
      togglep(GPIOC, GPIO_PIN_8);
      /*
      read2 = response();
      if(read2=='2'){
        togglep(GPIOC, GPIO_PIN_8);
        transmitA("orange, toggle\r\n");
        o = !o;
      }else if(read2=='1'){
        if(!o){
          togglep(GPIOC, GPIO_PIN_8);
          o=1;
        }
        transmitA("orange, on\r\n");
      }else if(read2=='0'){
        if(o){
          togglep(GPIOC, GPIO_PIN_8);
          o=0;
        }
        transmitA("orange, off\r\n");
      }else{
        transmitA("ERROR input not valid\r\n");
      }
      */
      sb = 0;
    }else{
      transmitA("ERROR input not valid\r\n");
      sb = 0;
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
