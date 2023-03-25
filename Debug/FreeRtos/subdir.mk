################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRtos/croutine.c \
../FreeRtos/event_groups.c \
../FreeRtos/list.c \
../FreeRtos/queue.c \
../FreeRtos/stream_buffer.c \
../FreeRtos/tasks.c \
../FreeRtos/timers.c 

OBJS += \
./FreeRtos/croutine.o \
./FreeRtos/event_groups.o \
./FreeRtos/list.o \
./FreeRtos/queue.o \
./FreeRtos/stream_buffer.o \
./FreeRtos/tasks.o \
./FreeRtos/timers.o 

C_DEPS += \
./FreeRtos/croutine.d \
./FreeRtos/event_groups.d \
./FreeRtos/list.d \
./FreeRtos/queue.d \
./FreeRtos/stream_buffer.d \
./FreeRtos/tasks.d \
./FreeRtos/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRtos/%.o: ../FreeRtos/%.c FreeRtos/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/FreeRtos" -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/FreeRtos/portable/GCC/ARM_CM4F" -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/FreeRtos/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRtos

clean-FreeRtos:
	-$(RM) ./FreeRtos/croutine.d ./FreeRtos/croutine.o ./FreeRtos/event_groups.d ./FreeRtos/event_groups.o ./FreeRtos/list.d ./FreeRtos/list.o ./FreeRtos/queue.d ./FreeRtos/queue.o ./FreeRtos/stream_buffer.d ./FreeRtos/stream_buffer.o ./FreeRtos/tasks.d ./FreeRtos/tasks.o ./FreeRtos/timers.d ./FreeRtos/timers.o

.PHONY: clean-FreeRtos

