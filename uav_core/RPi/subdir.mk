################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../devices.cpp \
../interface.cpp \
../messages_avr.cpp \
../messages_gen.cpp 

OBJS += \
./devices.o \
./interface.o \
./messages_avr.o \
./messages_gen.o 

CPP_DEPS += \
./devices.d \
./interface.d \
./messages_avr.d \
./messages_gen.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__RPI__ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


