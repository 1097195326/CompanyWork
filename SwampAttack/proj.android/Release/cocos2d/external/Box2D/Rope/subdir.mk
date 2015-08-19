################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/Box2D/Rope/b2Rope.cpp 

OBJS += \
./cocos2d/external/Box2D/Rope/b2Rope.o 

CPP_DEPS += \
./cocos2d/external/Box2D/Rope/b2Rope.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/external/Box2D/Rope/b2Rope.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/Box2D/Rope/b2Rope.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


