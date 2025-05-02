################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Library/F2837xD_CodeStartBranch.obj" \
"./Library/F2837xD_GlobalVariableDefs.obj" \
"./Library/F2837xD_Gpio.obj" \
"./Library/F2837xD_Ipc.obj" \
"./Library/F2837xD_SysCtrl.obj" \
"./Library/F2837xD_usDelay.obj" \
"./User/main.obj" \
$(GEN_CMDS__FLAG) \
-l"F:/STM32SSC/Note/TI/DSP/TI-C2000-TMS320F28379D/Code/Library/F28379D_Headers/cmd/F2837xD_Headers_nonBIOS_cpu1.cmd" \
-l"F:/STM32SSC/Note/TI/DSP/TI-C2000-TMS320F28379D/Code/Library/F28379D_Common/cmd/2837xD_RAM_lnk_cpu1.cmd" \
-l"F:/STM32SSC/Note/TI/DSP/TI-C2000-TMS320F28379D/Code/Library/F28379D_Common/lib/rts2800_fpu32.lib" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include Library/subdir_vars.mk
-include User/subdir_vars.mk
-include Library/subdir_rules.mk
-include User/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
1_F28379D_Test_cpu1.out \

EXE_OUTPUTS__QUOTED += \
"1_F28379D_Test_cpu1.out" \

BIN_OUTPUTS += \
1_F28379D_Test_cpu1.hex \

BIN_OUTPUTS__QUOTED += \
"1_F28379D_Test_cpu1.hex" \


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "1_F28379D_Test_cpu1.out"

# Tool invocations
1_F28379D_Test_cpu1.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"1_F28379D_Test_cpu1.map" --stack_size=0x200 --warn_sections -i"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/lib" -i"F:/STM32SSC/Note/TI/DSP/TI-C2000-TMS320F28379D/Code/Library/F28379D_Common/cmd" -i"F:/STM32SSC/Note/TI/DSP/TI-C2000-TMS320F28379D/Code/Library/F28379D_Headers/cmd" -i"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="1_F28379D_Test_cpu1_linkInfo.xml" --entry_point=_c_int00 --rom_model -o "1_F28379D_Test_cpu1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

1_F28379D_Test_cpu1.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/hex2000"  -o "1_F28379D_Test_cpu1.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Library\F2837xD_CodeStartBranch.obj" "Library\F2837xD_GlobalVariableDefs.obj" "Library\F2837xD_Gpio.obj" "Library\F2837xD_Ipc.obj" "Library\F2837xD_SysCtrl.obj" "Library\F2837xD_usDelay.obj" "User\main.obj" 
	-$(RM) "Library\F2837xD_GlobalVariableDefs.d" "Library\F2837xD_Gpio.d" "Library\F2837xD_Ipc.d" "Library\F2837xD_SysCtrl.d" "User\main.d" 
	-$(RM) "Library\F2837xD_CodeStartBranch.d" "Library\F2837xD_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

