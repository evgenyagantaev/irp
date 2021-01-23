################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l051xx.s 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l051xx.o 

S_DEPS += \
./Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l051xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l051xx.o: ../Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l051xx.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp -MMD -MP -MF"Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l051xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

