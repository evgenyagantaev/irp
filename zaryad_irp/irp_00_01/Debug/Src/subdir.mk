################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/battery.c \
../Src/battery_control_task.c \
../Src/button.c \
../Src/button_polling_task.c \
../Src/ext_pow_control_task.c \
../Src/external_power.c \
../Src/gpio.c \
../Src/int_adc_measure_task.c \
../Src/internal_adc.c \
../Src/main.c \
../Src/putchar.c \
../Src/spi.c \
../Src/spi_pipe.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/tim.c \
../Src/time_management_task.c \
../Src/usart.c 

OBJS += \
./Src/adc.o \
./Src/battery.o \
./Src/battery_control_task.o \
./Src/button.o \
./Src/button_polling_task.o \
./Src/ext_pow_control_task.o \
./Src/external_power.o \
./Src/gpio.o \
./Src/int_adc_measure_task.o \
./Src/internal_adc.o \
./Src/main.o \
./Src/putchar.o \
./Src/spi.o \
./Src/spi_pipe.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/tim.o \
./Src/time_management_task.o \
./Src/usart.o 

C_DEPS += \
./Src/adc.d \
./Src/battery.d \
./Src/battery_control_task.d \
./Src/button.d \
./Src/button_polling_task.d \
./Src/ext_pow_control_task.d \
./Src/external_power.d \
./Src/gpio.d \
./Src/int_adc_measure_task.d \
./Src/internal_adc.d \
./Src/main.d \
./Src/putchar.d \
./Src/spi.d \
./Src/spi_pipe.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/tim.d \
./Src/time_management_task.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L051xx -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/CMSIS/Include" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


