################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/openal/OpenALDecoder.cpp \
/Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/openal/SimpleAudioEngineOpenAL.cpp 

OBJS += \
./cocos2d/cocos/audio/openal/OpenALDecoder.o \
./cocos2d/cocos/audio/openal/SimpleAudioEngineOpenAL.o 

CPP_DEPS += \
./cocos2d/cocos/audio/openal/OpenALDecoder.d \
./cocos2d/cocos/audio/openal/SimpleAudioEngineOpenAL.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/cocos/audio/openal/OpenALDecoder.o: /Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/openal/OpenALDecoder.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/cocos/audio/openal/SimpleAudioEngineOpenAL.o: /Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/openal/SimpleAudioEngineOpenAL.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


