#include "stm32l0xx_hal.h"

extern UART_HandleTypeDef huart1;

void putchar_for_test(int ch)
{
    uint8_t symbol = (uint8_t)ch;
    HAL_UART_Transmit(&huart1, &symbol, 1, 500);  // for production board

    //return ch;
}

