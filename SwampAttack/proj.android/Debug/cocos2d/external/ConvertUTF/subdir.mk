################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTFWrapper.cpp 

C_SRCS += \
/Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTF.c 

OBJS += \
./cocos2d/external/ConvertUTF/ConvertUTF.o \
./cocos2d/external/ConvertUTF/ConvertUTFWrapper.o 

CPP_DEPS += \
./cocos2d/external/ConvertUTF/ConvertUTFWrapper.d 

C_DEPS += \
./cocos2d/external/ConvertUTF/ConvertUTF.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/external/ConvertUTF/ConvertUTF.o: /Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTF.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/external/ConvertUTF/ConvertUTFWrapper.o: /Users/oceantech02/work/Program/CompanyWork/SwampAttack/cocos2d/external/ConvertUTF/ConvertUTFWrapper.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


