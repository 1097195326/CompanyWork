################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../jni/hellocpp/UCSdkJniHelper.cpp \
../jni/hellocpp/main.cpp 

OBJS += \
./jni/hellocpp/UCSdkJniHelper.o \
./jni/hellocpp/main.o 

CPP_DEPS += \
./jni/hellocpp/UCSdkJniHelper.d \
./jni/hellocpp/main.d 


# Each subdirectory must supply rules for building sources it contributes
jni/hellocpp/%.o: ../jni/hellocpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


