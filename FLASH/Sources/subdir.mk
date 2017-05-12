################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/DAC.c" \
"../Sources/I2C.c" \
"../Sources/OLED.c" \
"../Sources/PWM.c" \
"../Sources/SPI.c" \
"../Sources/SYSINIT.c" \
"../Sources/UART.c" \
"../Sources/arm_cm0.c" \
"../Sources/main.c" \
"../Sources/mcg.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/DAC.c \
../Sources/I2C.c \
../Sources/OLED.c \
../Sources/PWM.c \
../Sources/SPI.c \
../Sources/SYSINIT.c \
../Sources/UART.c \
../Sources/arm_cm0.c \
../Sources/main.c \
../Sources/mcg.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/ADC.o \
./Sources/DAC.o \
./Sources/I2C.o \
./Sources/OLED.o \
./Sources/PWM.o \
./Sources/SPI.o \
./Sources/SYSINIT.o \
./Sources/UART.o \
./Sources/arm_cm0.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/ADC.d \
./Sources/DAC.d \
./Sources/I2C.d \
./Sources/OLED.d \
./Sources/PWM.d \
./Sources/SPI.d \
./Sources/SYSINIT.d \
./Sources/UART.d \
./Sources/arm_cm0.d \
./Sources/main.d \
./Sources/mcg.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/ADC.o" \
"./Sources/DAC.o" \
"./Sources/I2C.o" \
"./Sources/OLED.o" \
"./Sources/PWM.o" \
"./Sources/SPI.o" \
"./Sources/SYSINIT.o" \
"./Sources/UART.o" \
"./Sources/arm_cm0.o" \
"./Sources/main.o" \
"./Sources/mcg.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/ADC.d" \
"./Sources/DAC.d" \
"./Sources/I2C.d" \
"./Sources/OLED.d" \
"./Sources/PWM.d" \
"./Sources/SPI.d" \
"./Sources/SYSINIT.d" \
"./Sources/UART.d" \
"./Sources/arm_cm0.d" \
"./Sources/main.d" \
"./Sources/mcg.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/ADC.o \
./Sources/DAC.o \
./Sources/I2C.o \
./Sources/OLED.o \
./Sources/PWM.o \
./Sources/SPI.o \
./Sources/SYSINIT.o \
./Sources/UART.o \
./Sources/arm_cm0.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC.o: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/DAC.o: ../Sources/DAC.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/DAC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/DAC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/I2C.o: ../Sources/I2C.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/I2C.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/I2C.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/OLED.o: ../Sources/OLED.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/OLED.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/OLED.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PWM.o: ../Sources/PWM.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PWM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PWM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SPI.o: ../Sources/SPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SPI.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SYSINIT.o: ../Sources/SYSINIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SYSINIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SYSINIT.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UART.o: ../Sources/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UART.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/arm_cm0.o: ../Sources/arm_cm0.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/arm_cm0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/arm_cm0.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcg.o: ../Sources/mcg.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcg.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


