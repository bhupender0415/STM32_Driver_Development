# Reading Multiple ADC Channels in STM32 Using Interrupts - Example Application

This guide demonstrates how to configure and read multiple ADC (Analog-to-Digital Converter) channels in STM32 microcontrollers using interrupts. The example application provided utilizes STM32CubeIDE and the HAL (Hardware Abstraction Layer) library.

## Prerequisites

- Vscode
- PlatformIO
- Basic understanding of STM32 microcontroller programming
- C/C++ programming

## ADC Configuration (`adc.c`)

The `adc.c` file contains the initialization and configuration of the ADC peripheral.

### Function: `ADC_init()`

This function initializes the ADC peripheral and configures it to read from multiple channels. It also sets up the GPIO pins for ADC input and configures the ADC channels, sampling times, and interrupt.

```c
void ADC_init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    ADC_ChannelConfTypeDef sConfig;

    // enable clock for GPIOA, GPIOB, GPIOC
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // configure GPIOA pins for ADC
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // configure GPIOB pins for ADC
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // configure GPIOC pins for ADC
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // configure ADC for continous conversion
    __HAL_RCC_ADC1_CLK_ENABLE();
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = ENABLE; // enable scan mode
    hadc1.Init.ContinuousConvMode = ENABLE; // continuous conversion mode
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 6; // one conversion
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    HAL_ADC_Init(&hadc1);

    // configure ADC channel 0
    sConfig.Channel = ADC_CHANNEL_0; // PA0
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);  

    // configure ADC channel 1
    sConfig.Channel = ADC_CHANNEL_1; // PA1
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // configure ADC channel 2
    sConfig.Channel = ADC_CHANNEL_4; // PA4
    sConfig.Rank = 3;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // configure ADC channel 3
    sConfig.Channel = ADC_CHANNEL_8; // PB0
    sConfig.Rank = 4;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // configure ADC channel 4
    sConfig.Channel = ADC_CHANNEL_10; // PC0
    sConfig.Rank = 5;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // configure ADC channel 5
    sConfig.Channel = ADC_CHANNEL_11; // PC1
    sConfig.Rank = 6;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // enable adc interrupt
    NVIC_SetPriority(ADC_IRQn, 0);
    NVIC_EnableIRQ(ADC_IRQn);  
}
```

### ADC Interrupt Handler: `HAL_ADC_ConvCpltCallback()`

This callback function is called when an ADC conversion is complete. It stores the ADC values into an array for further processing.

```c
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1)
    {
        // Store ADC values into array
        adc_value[ind] = HAL_ADC_GetValue(hadc);
        ind++;
        if(ind == 6)
        {
            ind = 0;
        }
        HAL_ADC_Start_IT(&hadc1); // Start next ADC conversion with interrupts enabled
    }
}
```

## Main Application (`main.c`)

The `main.c` file contains the main application code where the ADC is initialized and ADC values are read.

### Initialization

The `main()` function initializes the HAL library, UART communication, and ADC peripheral. It starts ADC conversions with interrupts enabled.

```c
int main()
{
    HAL_Init();
    uart_init(); // Initialize UART communication
    ADC_init(); // Initialize ADC
    HAL_ADC_Start_IT(&hadc1); // Start ADC conversion with interrupts enabled

    // Main program loop
    while(1)
    {
        // Print ADC values to UART
        printf("ADC value: %ld %ld %ld %ld %ld %ld\n", adc_value[0], adc_value[1], adc_value[2], adc_value[3], adc_value[4], adc_value[5]);
        HAL_Delay(2000); // Delay for 2 seconds
    }
}
```

## Conclusion

This guide outlines the steps to read multiple ADC channels in an STM32 microcontroller using interrupts. The provided example application initializes the ADC peripheral, starts ADC conversions with interrupts enabled, and stores the ADC values into an array for further processing.

---

Feel free to customize the README file according to your project requirements and provide additional details if needed.
