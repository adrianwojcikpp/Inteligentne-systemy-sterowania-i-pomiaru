################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/main.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_api.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_config.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_interface.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_math.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_parameters.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_tasks.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/motor_control_protocol.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/motorcontrol.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/regular_conversion_manager.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/stm32f0xx_hal_msp.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/stm32f0xx_it.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/stm32f0xx_mc_it.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/ui_task.c \
C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/user_interface.c 

OBJS += \
./Application/User/main.o \
./Application/User/mc_api.o \
./Application/User/mc_config.o \
./Application/User/mc_interface.o \
./Application/User/mc_math.o \
./Application/User/mc_parameters.o \
./Application/User/mc_tasks.o \
./Application/User/motor_control_protocol.o \
./Application/User/motorcontrol.o \
./Application/User/regular_conversion_manager.o \
./Application/User/stm32f0xx_hal_msp.o \
./Application/User/stm32f0xx_it.o \
./Application/User/stm32f0xx_mc_it.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o \
./Application/User/ui_task.o \
./Application/User/user_interface.o 

C_DEPS += \
./Application/User/main.d \
./Application/User/mc_api.d \
./Application/User/mc_config.d \
./Application/User/mc_interface.d \
./Application/User/mc_math.d \
./Application/User/mc_parameters.d \
./Application/User/mc_tasks.d \
./Application/User/motor_control_protocol.d \
./Application/User/motorcontrol.d \
./Application/User/regular_conversion_manager.d \
./Application/User/stm32f0xx_hal_msp.d \
./Application/User/stm32f0xx_it.d \
./Application/User/stm32f0xx_mc_it.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d \
./Application/User/ui_task.d \
./Application/User/user_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/main.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/main.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/mc_api.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_api.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/mc_config.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_config.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/mc_interface.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_interface.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/mc_math.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_math.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/mc_parameters.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_parameters.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/mc_tasks.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/mc_tasks.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/motor_control_protocol.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/motor_control_protocol.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/motorcontrol.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/motorcontrol.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/regular_conversion_manager.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/regular_conversion_manager.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/stm32f0xx_hal_msp.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/stm32f0xx_hal_msp.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/stm32f0xx_it.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/stm32f0xx_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/stm32f0xx_mc_it.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/stm32f0xx_mc_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/%.o Application/User/%.su: ../Application/User/%.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/ui_task.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/ui_task.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/user_interface.o: C:/PP/Dydaktyka/MATERIALY/ISPiS_MATERIALY/ISPiS_PRZYKLADY/L01/smiglo/Src/user_interface.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM0 -DUSE_HAL_DRIVER -DSTM32F031x6 -c -I../../Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/Any/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/MCLib/F0xx/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/UILibrary/Inc -I../../MCSDK_v5.4.8/MotorControl/MCSDK/SystemDriveParams -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User

clean-Application-2f-User:
	-$(RM) ./Application/User/main.d ./Application/User/main.o ./Application/User/main.su ./Application/User/mc_api.d ./Application/User/mc_api.o ./Application/User/mc_api.su ./Application/User/mc_config.d ./Application/User/mc_config.o ./Application/User/mc_config.su ./Application/User/mc_interface.d ./Application/User/mc_interface.o ./Application/User/mc_interface.su ./Application/User/mc_math.d ./Application/User/mc_math.o ./Application/User/mc_math.su ./Application/User/mc_parameters.d ./Application/User/mc_parameters.o ./Application/User/mc_parameters.su ./Application/User/mc_tasks.d ./Application/User/mc_tasks.o ./Application/User/mc_tasks.su ./Application/User/motor_control_protocol.d ./Application/User/motor_control_protocol.o ./Application/User/motor_control_protocol.su ./Application/User/motorcontrol.d ./Application/User/motorcontrol.o ./Application/User/motorcontrol.su ./Application/User/regular_conversion_manager.d ./Application/User/regular_conversion_manager.o ./Application/User/regular_conversion_manager.su ./Application/User/stm32f0xx_hal_msp.d ./Application/User/stm32f0xx_hal_msp.o ./Application/User/stm32f0xx_hal_msp.su ./Application/User/stm32f0xx_it.d ./Application/User/stm32f0xx_it.o ./Application/User/stm32f0xx_it.su ./Application/User/stm32f0xx_mc_it.d ./Application/User/stm32f0xx_mc_it.o ./Application/User/stm32f0xx_mc_it.su ./Application/User/syscalls.d ./Application/User/syscalls.o ./Application/User/syscalls.su ./Application/User/sysmem.d ./Application/User/sysmem.o ./Application/User/sysmem.su ./Application/User/ui_task.d ./Application/User/ui_task.o ./Application/User/ui_task.su ./Application/User/user_interface.d ./Application/User/user_interface.o ./Application/User/user_interface.su

.PHONY: clean-Application-2f-User

