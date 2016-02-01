################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/xxhash/xxhash.c 

OBJS += \
./cocos2d/external/xxhash/xxhash.o 

C_DEPS += \
./cocos2d/external/xxhash/xxhash.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/external/xxhash/xxhash.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/xxhash/xxhash.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


