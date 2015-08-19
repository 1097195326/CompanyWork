################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/AudioEngine.cpp 

OBJS += \
./cocos2d/cocos/audio/AudioEngine.o 

CPP_DEPS += \
./cocos2d/cocos/audio/AudioEngine.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/cocos/audio/AudioEngine.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/AudioEngine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


