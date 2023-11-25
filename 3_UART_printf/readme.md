# STM32 UART printf Retargeting Example

This is an example project that demonstrates how to retarget the `printf` function to UART on an STM32 microcontroller using PlatformIO.

## Prerequisites

- STM32 microcontroller board
- PlatformIO IDE

## Getting Started

1. Clone or download this repository.
2. Open the project in PlatformIO IDE.
3. Connect your STM32 board to your computer.
4. Build and upload the code to your STM32 board.
5. Open a serial terminal (e.g., PuTTY, Tera Term) and connect to the UART port of your STM32 board.
6. You should see the "Hello World" message being printed repeatedly in the serial terminal.

## Configuration

To configure the UART settings, modify the `uart_init` function in the `main.c` file. You can change the baud rate, data bits, parity, stop bits, and other UART parameters according to your requirements.

```c
void uart_init()
{
    // Configure GPIO module as AF
    // ...

    // Configure USART module
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);
}
```


## License

This project is licensed under the [MIT License](vscode-file://vscode-app/c:/Users/Bhupender%20Dangwal/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "LICENSE").

## Acknowledgments

* [STM32Cube HAL](vscode-file://vscode-app/c:/Users/Bhupender%20Dangwal/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "https://www.st.com/en/embedded-software/stm32cube-mcu-packages.html")
* [PlatformIO](vscode-file://vscode-app/c:/Users/Bhupender%20Dangwal/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html "https://platformio.org/")

Feel free to modify and customize the README file according to your specific project requirements.
