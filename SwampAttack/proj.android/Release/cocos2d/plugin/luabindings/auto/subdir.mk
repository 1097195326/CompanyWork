################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/plugin/luabindings/auto/lua_cocos2dx_pluginx_auto.cpp 

OBJS += \
./cocos2d/plugin/luabindings/auto/lua_cocos2dx_pluginx_auto.o 

CPP_DEPS += \
./cocos2d/plugin/luabindings/auto/lua_cocos2dx_pluginx_auto.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/plugin/luabindings/auto/lua_cocos2dx_pluginx_auto.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/plugin/luabindings/auto/lua_cocos2dx_pluginx_auto.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


