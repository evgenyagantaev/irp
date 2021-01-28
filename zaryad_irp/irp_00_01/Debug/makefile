################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tests/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
irp_00_01.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
irp_00_01.list \

OBJCOPY_BIN += \
irp_00_01.bin \


# All Target
all: irp_00_01.elf secondary-outputs

# Tool invocations
irp_00_01.elf: $(OBJS) $(USER_OBJS) ../STM32L051C6Tx_FLASH.ld
	arm-none-eabi-gcc -o "irp_00_01.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"../STM32L051C6Tx_FLASH.ld" --specs=nosys.specs -Wl,-Map="irp_00_01.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

irp_00_01.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "irp_00_01.list"
	@echo 'Finished building: $@'
	@echo ' '

irp_00_01.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "irp_00_01.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
