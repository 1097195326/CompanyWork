################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/oceantech02/work/Program/CompanyWork/SwampAttack/Classes/json/json_reader.cpp \
/Users/oceantech02/work/Program/CompanyWork/SwampAttack/Classes/json/json_value.cpp \
/Users/oceantech02/work/Program/CompanyWork/SwampAttack/Classes/json/json_writer.cpp 

OBJS += \
./Classes/json/json_reader.o \
./Classes/json/json_value.o \
./Classes/json/json_writer.o 

CPP_DEPS += \
./Classes/json/json_reader.d \
./Classes/json/json_value.d \
./Classes/json/json_writer.d 


# Each subdirectory must supply rules for building sources it contributes
Classes/json/json_reader.o: /Users/oceantech02/work/Program/CompanyWork/SwampAttack/Classes/json/json_reader.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/json/json_value.o: /Users/oceantech02/work/Program/CompanyWork/SwampAttack/Classes/json/json_value.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/json/json_writer.o: /Users/oceantech02/work/Program/CompanyWork/SwampAttack/Classes/json/json_writer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


