################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/unzip/ioapi.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/unzip/ioapi_mem.cpp \
/Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/unzip/unzip.cpp 

OBJS += \
./cocos2d/external/unzip/ioapi.o \
./cocos2d/external/unzip/ioapi_mem.o \
./cocos2d/external/unzip/unzip.o 

CPP_DEPS += \
./cocos2d/external/unzip/ioapi.d \
./cocos2d/external/unzip/ioapi_mem.d \
./cocos2d/external/unzip/unzip.d 


# Each subdirectory must supply rules for building sources it contributes
cocos2d/external/unzip/ioapi.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/unzip/ioapi.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/external/unzip/ioapi_mem.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/unzip/ioapi_mem.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cocos2d/external/unzip/unzip.o: /Users/zhanghongxing/work/Program/CompanyWork/SwampAttack/cocos2d/external/unzip/unzip.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


