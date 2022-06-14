/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define SVD123_anodes_Pin GPIO_PIN_0
#define SVD123_anodes_Port GPIOA
#define SVD456_anodes_Pin GPIO_PIN_1
#define SVD456_anodes_Port GPIOA
//***********************************

#define ind_7_seg_1_Pin GPIO_PIN_2
#define ind_7_seg_1_Port GPIOA
#define ind_7_seg_2_Pin GPIO_PIN_3
#define ind_7_seg_2_Port GPIOA
#define ind_7_seg_4_Pin GPIO_PIN_4
#define ind_7_seg_4_Port GPIOA
#define ind_7_seg_8_Pin GPIO_PIN_5
#define ind_7_seg_8_Port GPIOA

//************************************
#define SVD1_4_catode_Pin GPIO_PIN_6
#define SVD1_4_catode_Port GPIOA
#define SVD2_5_catode_Pin GPIO_PIN_7
#define SVD2_5_catode_Port GPIOA
#define SVD3_6_catode_Pin GPIO_PIN_8
#define SVD3_6_catode_Port GPIOA
//************************************

#define chipsel1_out_Pin GPIO_PIN_0
#define chipsel1_out_GPIO_Port GPIOB
#define chipsel2_out_Pin GPIO_PIN_1
#define chipsel2_out_GPIO_Port GPIOB
#define chipsel3_out_Pin GPIO_PIN_2
#define chipsel3_out_GPIO_Port GPIOB
#define ext_watchdog_out_Pin GPIO_PIN_12
#define ext_watchdog_out_GPIO_Port GPIOB
#define charge75_led_green_out_Pin GPIO_PIN_10
#define charge75_led_green_out_GPIO_Port GPIOA
#define charge50_led_green_out_Pin GPIO_PIN_11
#define charge50_led_green_out_GPIO_Port GPIOA
#define charge25_led_green_out_Pin GPIO_PIN_12
#define charge25_led_green_out_GPIO_Port GPIOA
#define ctc_onoff_button_exti15_Pin GPIO_PIN_15
#define ctc_onoff_button_exti15_GPIO_Port GPIOA
#define chipsel4_out_Pin GPIO_PIN_3
#define chipsel4_out_GPIO_Port GPIOB
#define relei_control_out_Pin GPIO_PIN_8
#define relei_control_out_GPIO_Port GPIOB
#define rst_out_Pin GPIO_PIN_9
#define rst_out_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
