################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/tinyxml2/tinyxml2.cpp 

OBJS += \
./cocos2d/external/tinyxml2/tinyxml2.o 

CPP_DEPS += \
./cocos2d/external/tinyxml2/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/external/tinyxml2/tinyxml2.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/tinyxml2/tinyxml2.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


