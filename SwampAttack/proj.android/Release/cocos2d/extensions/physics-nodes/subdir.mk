################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/extensions/physics-nodes/CCPhysicsDebugNode.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/extensions/physics-nodes/CCPhysicsSprite.cpp 

OBJS += \
./cocos2d/extensions/physics-nodes/CCPhysicsDebugNode.o \
./cocos2d/extensions/physics-nodes/CCPhysicsSprite.o 

CPP_DEPS += \
./cocos2d/extensions/physics-nodes/CCPhysicsDebugNode.d \
./cocos2d/extensions/physics-nodes/CCPhysicsSprite.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/extensions/physics-nodes/CCPhysicsDebugNode.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/extensions/physics-nodes/CCPhysicsDebugNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/extensions/physics-nodes/CCPhysicsSprite.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/extensions/physics-nodes/CCPhysicsSprite.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


