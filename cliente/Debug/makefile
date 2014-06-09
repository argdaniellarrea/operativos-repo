################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: cliente

dependents:
	-cd /home/utnso/git/so-commons-library/src/Debug && $(MAKE) all
	-cd /home/utnso/git/operativos-repo/sockets/Debug && $(MAKE) all

# Tool invocations
cliente: $(OBJS) $(USER_OBJS) /home/utnso/git/so-commons-library/src/Debug/libcommons.so /home/utnso/git/operativos-repo/sockets/Debug/libsockets-commons.so
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/home/utnso/git/operativos-repo/sockets/Debug" -L"/home/utnso/git/so-commons-library/src/Debug" -o "cliente" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) cliente
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/utnso/git/so-commons-library/src/Debug/libcommons.so:
/home/utnso/git/operativos-repo/sockets/Debug/libsockets-commons.so:

-include ../makefile.targets
