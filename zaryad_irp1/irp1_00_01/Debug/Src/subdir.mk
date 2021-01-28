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
../Src/eeprom_storage_obj.c \
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
./Src/eeprom_storage_obj.o \
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
./Src/eeprom_storage_obj.d \
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
Src/battery_measurement_task.o: ../Src/battery_measurement_task.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/battery_measurement_task.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/battery_obj.o: ../Src/battery_obj.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/battery_obj.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/charge_level_detector_obj.o: ../Src/charge_level_detector_obj.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/charge_level_detector_obj.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/charger_obj.o: ../Src/charger_obj.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/charger_obj.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/coulombcounter_obj.o: ../Src/coulombcounter_obj.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/coulombcounter_obj.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/eeprom_storage_obj.o: ../Src/eeprom_storage_obj.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/eeprom_storage_obj.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/gpio.o: ../Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/i2c.o: ../Src/i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/i2c_lowlevel.o: ../Src/i2c_lowlevel.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/i2c_lowlevel.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/message_interpreter_task.o: ../Src/message_interpreter_task.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/message_interpreter_task.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/message_queue.o: ../Src/message_queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/message_queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/putchar.o: ../Src/putchar.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/putchar.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/spi.o: ../Src/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/spi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/spi1_irq_handler.o: ../Src/spi1_irq_handler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/spi1_irq_handler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/spi1_transceiver.o: ../Src/spi1_transceiver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/spi1_transceiver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/stm32l0xx_hal_msp.o: ../Src/stm32l0xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32l0xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/stm32l0xx_it.o: ../Src/stm32l0xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32l0xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/switch_obj.o: ../Src/switch_obj.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/switch_obj.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/tim.o: ../Src/tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/tim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/time_management_task.o: ../Src/time_management_task.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/time_management_task.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/usart.o: ../Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/usart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

