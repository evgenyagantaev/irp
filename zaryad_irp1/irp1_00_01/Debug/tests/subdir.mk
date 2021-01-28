################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tests/test_hat.c \
../tests/test_i2c_lowlevel.c \
../tests/test_template_runner.c \
../tests/unity.c 

OBJS += \
./tests/test_hat.o \
./tests/test_i2c_lowlevel.o \
./tests/test_template_runner.o \
./tests/unity.o 

C_DEPS += \
./tests/test_hat.d \
./tests/test_i2c_lowlevel.d \
./tests/test_template_runner.d \
./tests/unity.d 


# Each subdirectory must supply rules for building sources it contributes
tests/test_hat.o: ../tests/test_hat.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"tests/test_hat.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
tests/test_i2c_lowlevel.o: ../tests/test_i2c_lowlevel.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"tests/test_i2c_lowlevel.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
tests/test_template_runner.o: ../tests/test_template_runner.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"tests/test_template_runner.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
tests/unity.o: ../tests/unity.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"tests/unity.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

