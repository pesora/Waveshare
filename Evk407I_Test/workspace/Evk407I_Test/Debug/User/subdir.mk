################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Protocol.c \
../User/pid.c \
../User/ustils.c 

OBJS += \
./User/Protocol.o \
./User/pid.o \
./User/ustils.o 

C_DEPS += \
./User/Protocol.d \
./User/pid.d \
./User/ustils.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o User/%.su User/%.cyclo: ../User/%.c User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"F:/7.Sunshine/Waveshare/Evk407I_Test/workspace/Evk407I_Test/User" -I"F:/7.Sunshine/Waveshare/Evk407I_Test/workspace/Evk407I_Test/Utils" -I"F:/7.Sunshine/Waveshare/Evk407I_Test/workspace/Evk407I_Test/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User

clean-User:
	-$(RM) ./User/Protocol.cyclo ./User/Protocol.d ./User/Protocol.o ./User/Protocol.su ./User/pid.cyclo ./User/pid.d ./User/pid.o ./User/pid.su ./User/ustils.cyclo ./User/ustils.d ./User/ustils.o ./User/ustils.su

.PHONY: clean-User

