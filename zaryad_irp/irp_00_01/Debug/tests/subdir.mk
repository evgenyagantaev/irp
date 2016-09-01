################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tests/test_code_template.c \
../tests/unity.c 

OBJS += \
./tests/test_code_template.o \
./tests/unity.o 

C_DEPS += \
./tests/test_code_template.d \
./tests/unity.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L051xx -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/CMSIS/Include" -I"C:/workspace/ac6_mars_workspace/l051workspace/fromcube/irp_github/zaryad_irp/irp_00_01/Drivers/CMSIS/Device/ST/STM32L0xx/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


