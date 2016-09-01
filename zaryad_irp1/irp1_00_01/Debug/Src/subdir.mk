################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/battery.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/i2c_lowlevel.c \
../Src/putchar.c \
../Src/spi.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/battery.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/i2c_lowlevel.o \
./Src/putchar.o \
./Src/spi.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/battery.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/i2c_lowlevel.d \
./Src/putchar.d \
./Src/spi.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L051xx -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/zaryad_irp1/irp1_00_01/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/zaryad_irp1/irp1_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/zaryad_irp1/irp1_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/zaryad_irp1/irp1_00_01/Drivers/CMSIS/Include" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/zaryad_irp1/irp1_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


