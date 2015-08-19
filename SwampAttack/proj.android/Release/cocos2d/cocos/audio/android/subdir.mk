################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/android/AudioEngine-inl.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/android/ccdandroidUtils.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/android/cddSimpleAudioEngine.cpp 

OBJS += \
./cocos2d/cocos/audio/android/AudioEngine-inl.o \
./cocos2d/cocos/audio/android/ccdandroidUtils.o \
./cocos2d/cocos/audio/android/cddSimpleAudioEngine.o 

CPP_DEPS += \
./cocos2d/cocos/audio/android/AudioEngine-inl.d \
./cocos2d/cocos/audio/android/ccdandroidUtils.d \
./cocos2d/cocos/audio/android/cddSimpleAudioEngine.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/cocos/audio/android/AudioEngine-inl.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/android/AudioEngine-inl.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/cocos/audio/android/ccdandroidUtils.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/android/ccdandroidUtils.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/cocos/audio/android/cddSimpleAudioEngine.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/audio/android/cddSimpleAudioEngine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


