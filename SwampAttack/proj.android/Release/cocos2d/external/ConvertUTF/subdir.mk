################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTFWrapper.cpp 

C_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTF.c 

OBJS += \
./cocos2d/external/ConvertUTF/ConvertUTF.o \
./cocos2d/external/ConvertUTF/ConvertUTFWrapper.o 

C_DEPS += \
./cocos2d/external/ConvertUTF/ConvertUTF.d 

CPP_DEPS += \
./cocos2d/external/ConvertUTF/ConvertUTFWrapper.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/external/ConvertUTF/ConvertUTF.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTF.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/external/ConvertUTF/ConvertUTFWrapper.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTFWrapper.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


