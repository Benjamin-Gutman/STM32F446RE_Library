################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../core/adc.c \
../core/dma.c \
../core/gpio.c \
../core/timer.c \
../core/usart.c 

OBJS += \
./core/adc.o \
./core/dma.o \
./core/gpio.o \
./core/timer.o \
./core/usart.o 

C_DEPS += \
./core/adc.d \
./core/dma.d \
./core/gpio.d \
./core/timer.d \
./core/usart.d 


# Each subdirectory must supply rules for building sources it contributes
core/%.o core/%.su core/%.cyclo: ../core/%.c core/subdir.mk
	$(error unable to generate command line)

clean: clean-core

clean-core:
	-$(RM) ./core/adc.cyclo ./core/adc.d ./core/adc.o ./core/adc.su ./core/dma.cyclo ./core/dma.d ./core/dma.o ./core/dma.su ./core/gpio.cyclo ./core/gpio.d ./core/gpio.o ./core/gpio.su ./core/timer.cyclo ./core/timer.d ./core/timer.o ./core/timer.su ./core/usart.cyclo ./core/usart.d ./core/usart.o ./core/usart.su

.PHONY: clean-core

