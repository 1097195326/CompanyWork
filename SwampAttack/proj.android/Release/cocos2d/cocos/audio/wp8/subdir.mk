################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/wp8/Audio.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/wp8/MediaStreamer.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/wp8/SimpleAudioEngine.cpp 

OBJS += \
./cocos2d/cocos/audio/wp8/Audio.o \
./cocos2d/cocos/audio/wp8/MediaStreamer.o \
./cocos2d/cocos/audio/wp8/SimpleAudioEngine.o 

CPP_DEPS += \
./cocos2d/cocos/audio/wp8/Audio.d \
./cocos2d/cocos/audio/wp8/MediaStreamer.d \
./cocos2d/cocos/audio/wp8/SimpleAudioEngine.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/cocos/audio/wp8/Audio.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/wp8/Audio.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/cocos/audio/wp8/MediaStreamer.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/wp8/MediaStreamer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/cocos/audio/wp8/SimpleAudioEngine.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/wp8/SimpleAudioEngine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


