################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../library_tests/gpio_test.c 

OBJS += \
./library_tests/gpio_test.o 

C_DEPS += \
./library_tests/gpio_test.d 


# Each subdirectory must supply rules for building sources it contributes
library_tests/%.o library_tests/%.su library_tests/%.cyclo: ../library_tests/%.c library_tests/subdir.mk
	$(error unable to generate command line)

clean: clean-library_tests

clean-library_tests:
	-$(RM) ./library_tests/gpio_test.cyclo ./library_tests/gpio_test.d ./library_tests/gpio_test.o ./library_tests/gpio_test.su

.PHONY: clean-library_tests

