################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/portable/GCC/ARM_CM4_MPU/port.c 

OBJS += \
./ThirdParty/portable/GCC/ARM_CM4_MPU/port.o 

C_DEPS += \
./ThirdParty/portable/GCC/ARM_CM4_MPU/port.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/portable/GCC/ARM_CM4_MPU/%.o: ../ThirdParty/portable/GCC/ARM_CM4_MPU/%.c ThirdParty/portable/GCC/ARM_CM4_MPU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/ThirdParty/include" -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/ThirdParty/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-portable-2f-GCC-2f-ARM_CM4_MPU

clean-ThirdParty-2f-portable-2f-GCC-2f-ARM_CM4_MPU:
	-$(RM) ./ThirdParty/portable/GCC/ARM_CM4_MPU/port.d ./ThirdParty/portable/GCC/ARM_CM4_MPU/port.o

.PHONY: clean-ThirdParty-2f-portable-2f-GCC-2f-ARM_CM4_MPU

