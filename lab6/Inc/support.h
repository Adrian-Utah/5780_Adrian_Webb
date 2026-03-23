

void Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void clockA(void);
void tempfunc(void);
void writep(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void togglep(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);