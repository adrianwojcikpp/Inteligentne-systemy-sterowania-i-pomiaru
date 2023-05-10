################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/Startup/startup_stm32f031c6tx.s 

OBJS += \
./Application/Startup/startup_stm32f031c6tx.o 

S_DEPS += \
./Application/Startup/startup_stm32f031c6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Startup/%.o: ../Application/Startup/%.s Application/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Application-2f-Startup

clean-Application-2f-Startup:
	-$(RM) ./Application/Startup/startup_stm32f031c6tx.d ./Application/Startup/startup_stm32f031c6tx.o

.PHONY: clean-Application-2f-Startup

