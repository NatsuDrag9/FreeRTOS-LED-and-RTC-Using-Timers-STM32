################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/croutine.c \
../ThirdParty/event_groups.c \
../ThirdParty/list.c \
../ThirdParty/queue.c \
../ThirdParty/stream_buffer.c \
../ThirdParty/tasks.c \
../ThirdParty/timers.c 

OBJS += \
./ThirdParty/croutine.o \
./ThirdParty/event_groups.o \
./ThirdParty/list.o \
./ThirdParty/queue.o \
./ThirdParty/stream_buffer.o \
./ThirdParty/tasks.o \
./ThirdParty/timers.o 

C_DEPS += \
./ThirdParty/croutine.d \
./ThirdParty/event_groups.d \
./ThirdParty/list.d \
./ThirdParty/queue.d \
./ThirdParty/stream_buffer.d \
./ThirdParty/tasks.d \
./ThirdParty/timers.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/%.o: ../ThirdParty/%.c ThirdParty/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/ThirdParty/include" -I"/home/rohitimandi/Desktop/Rohit/Personal/Partial_Work_and_Learning/Embedded Systems/STM32_Projects/FreeRtos_Practice/ThirdParty/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty

clean-ThirdParty:
	-$(RM) ./ThirdParty/croutine.d ./ThirdParty/croutine.o ./ThirdParty/event_groups.d ./ThirdParty/event_groups.o ./ThirdParty/list.d ./ThirdParty/list.o ./ThirdParty/queue.d ./ThirdParty/queue.o ./ThirdParty/stream_buffer.d ./ThirdParty/stream_buffer.o ./ThirdParty/tasks.d ./ThirdParty/tasks.o ./ThirdParty/timers.d ./ThirdParty/timers.o

.PHONY: clean-ThirdParty

