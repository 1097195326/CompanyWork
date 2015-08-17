################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/plugin/protocols/PluginManager.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/plugin/protocols/PluginParam.cpp 

OBJS += \
./cocos2d/plugin/protocols/PluginManager.o \
./cocos2d/plugin/protocols/PluginParam.o 

CPP_DEPS += \
./cocos2d/plugin/protocols/PluginManager.d \
./cocos2d/plugin/protocols/PluginParam.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/plugin/protocols/PluginManager.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/plugin/protocols/PluginManager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/plugin/protocols/PluginParam.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/plugin/protocols/PluginParam.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


