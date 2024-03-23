################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Library/DSP2833x_ADC_cal.obj" \
"./Library/DSP2833x_CodeStartBranch.obj" \
"./Library/DSP2833x_DefaultIsr.obj" \
"./Library/DSP2833x_GlobalVariableDefs.obj" \
"./Library/DSP2833x_Gpio.obj" \
"./Library/DSP2833x_PieCtrl.obj" \
"./Library/DSP2833x_PieVect.obj" \
"./Library/DSP2833x_SysCtrl.obj" \
"./Library/DSP2833x_usDelay.obj" \
"./User/main.obj" \
"../Library/DSP2833x_Headers_nonBIOS.cmd" \
"../Library/F28335.cmd" \
$(GEN_CMDS__FLAG) \
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
1_F28335_Test_demo.out \

EXE_OUTPUTS__QUOTED += \
"1_F28335_Test_demo.out" \

BIN_OUTPUTS += \
1_F28335_Test_demo.hex \

BIN_OUTPUTS__QUOTED += \
"1_F28335_Test_demo.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "1_F28335_Test_demo.out"

# Tool invocations
1_F28335_Test_demo.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -O2 --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"1_F28335_Test_demo.map" --stack_size=0x300 --warn_sections -i"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/lib" -i"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="1_F28335_Test_demo_linkInfo.xml" --rom_model -o "1_F28335_Test_demo.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

1_F28335_Test_demo.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"D:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/hex2000"  -o "1_F28335_Test_demo.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Library\DSP2833x_ADC_cal.obj" "Library\DSP2833x_CodeStartBranch.obj" "Library\DSP2833x_DefaultIsr.obj" "Library\DSP2833x_GlobalVariableDefs.obj" "Library\DSP2833x_Gpio.obj" "Library\DSP2833x_PieCtrl.obj" "Library\DSP2833x_PieVect.obj" "Library\DSP2833x_SysCtrl.obj" "Library\DSP2833x_usDelay.obj" "User\main.obj" 
	-$(RM) "Library\DSP2833x_DefaultIsr.d" "Library\DSP2833x_GlobalVariableDefs.d" "Library\DSP2833x_Gpio.d" "Library\DSP2833x_PieCtrl.d" "Library\DSP2833x_PieVect.d" "Library\DSP2833x_SysCtrl.d" "User\main.d" 
	-$(RM) "Library\DSP2833x_ADC_cal.d" "Library\DSP2833x_CodeStartBranch.d" "Library\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

