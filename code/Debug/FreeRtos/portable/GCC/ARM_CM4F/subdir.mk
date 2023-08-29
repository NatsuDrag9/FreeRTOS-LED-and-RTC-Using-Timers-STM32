################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRtos/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./FreeRtos/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./FreeRtos/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRtos/portable/GCC/ARM_CM4F/%.o: ../FreeRtos/portable/GCC/ARM_CM4F/%.c FreeRtos/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/FreeRtos" -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/FreeRtos/portable/GCC/ARM_CM4F" -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/FreeRtos/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRtos-2f-portable-2f-GCC-2f-ARM_CM4F

clean-FreeRtos-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./FreeRtos/portable/GCC/ARM_CM4F/port.d ./FreeRtos/portable/GCC/ARM_CM4F/port.o

.PHONY: clean-FreeRtos-2f-portable-2f-GCC-2f-ARM_CM4F

