################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/battery_measurement_task.c \
../Src/battery_obj.c \
../Src/charge_level_detector_obj.c \
../Src/charger_obj.c \
../Src/coulombcounter_obj.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/i2c_lowlevel.c \
../Src/message_interpreter_task.c \
../Src/message_queue.c \
../Src/putchar.c \
../Src/spi.c \
../Src/spi1_irq_handler.c \
../Src/spi1_transceiver.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/switch_obj.c \
../Src/tim.c \
../Src/time_management_task.c \
../Src/usart.c 

OBJS += \
./Src/battery_measurement_task.o \
./Src/battery_obj.o \
./Src/charge_level_detector_obj.o \
./Src/charger_obj.o \
./Src/coulombcounter_obj.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/i2c_lowlevel.o \
./Src/message_interpreter_task.o \
./Src/message_queue.o \
./Src/putchar.o \
./Src/spi.o \
./Src/spi1_irq_handler.o \
./Src/spi1_transceiver.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/switch_obj.o \
./Src/tim.o \
./Src/time_management_task.o \
./Src/usart.o 

C_DEPS += \
./Src/battery_measurement_task.d \
./Src/battery_obj.d \
./Src/charge_level_detector_obj.d \
./Src/charger_obj.d \
./Src/coulombcounter_obj.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/i2c_lowlevel.d \
./Src/message_interpreter_task.d \
./Src/message_queue.d \
./Src/putchar.d \
./Src/spi.d \
./Src/spi1_irq_handler.d \
./Src/spi1_transceiver.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/switch_obj.d \
./Src/tim.d \
./Src/time_management_task.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L051xx -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp1/irp1_00_01/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp1/irp1_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp1/irp1_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp1/irp1_00_01/Drivers/CMSIS/Include" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp1/irp1_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


