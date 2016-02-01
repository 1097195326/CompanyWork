################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/storage/local-storage/LocalStorage-android.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/storage/local-storage/LocalStorage.cpp 

OBJS += \
./cocos2d/cocos/storage/local-storage/LocalStorage-android.o \
./cocos2d/cocos/storage/local-storage/LocalStorage.o 

CPP_DEPS += \
./cocos2d/cocos/storage/local-storage/LocalStorage-android.d \
./cocos2d/cocos/storage/local-storage/LocalStorage.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/cocos/storage/local-storage/LocalStorage-android.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/storage/local-storage/LocalStorage-android.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/cocos/storage/local-storage/LocalStorage.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/cocos/storage/local-storage/LocalStorage.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


